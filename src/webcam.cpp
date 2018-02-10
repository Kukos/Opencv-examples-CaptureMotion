#include <webcam.hpp>
#include <unistd.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/video/background_segm.hpp>

#define WEBCAM_DEFAULT_FRAME_DELAY 30
/* lets assume that move is iff when >2% pixels was changed */
#define MOVE_FACTOR 0.02
#define MOVE_TRESHOLD(image) (image.total() * MOVE_FACTOR)

#define WEBCAM_FLIP
#define WEBCAM_TEST

Webcam::Webcam()
{
    thread_run = false;
    frame_delay = WEBCAM_DEFAULT_FRAME_DELAY;

    /* find webcam in devices list */
    webcam = new cv::VideoCapture(CV_CAP_ANY);
    is_work = webcam->isOpened();
}

Webcam::~Webcam()
{
    end();
    delete webcam;
}

int Webcam::get_width(void)
{
    if (!is_work_correctly())
        return -1;

    return (int)webcam->get(CV_CAP_PROP_FRAME_WIDTH);
}

int Webcam::get_height(void)
{
    if (!is_work_correctly())
        return -1;

    return (int)webcam->get(CV_CAP_PROP_FRAME_HEIGHT);
}

bool Webcam::is_work_correctly(void)
{
    return is_work;
}

void Webcam::start()
{
    if (!is_work_correctly())
        return;

    if (!thread_run)
    {
        thread_run = true;
        thread = std::thread(&Webcam::run, this);
    }
}

void Webcam::end()
{
    if (!is_work_correctly())
        return;

    if (thread_run)
    {
        thread_run = false;
        if(thread.joinable())
            thread.join();
    }
}

void Webcam::run()
{
    cv::Ptr<cv::BackgroundSubtractor> bsm2;

    /* create windows to show resilt if test mode */
    windows_create();

    /* parameters set in experimetic way */
    const int history = 500;
    const double var_treshold = 64;
    const bool shadow = false;
    bsm2 = cv::createBackgroundSubtractorMOG2(history, var_treshold, shadow);

    if (!is_work_correctly())
        return;

    while (thread_run)
    {
        /* capture single frame */
        capture_frame(frame);

        /* create image from frame*/
        images_create(frame);

        /* substract frames to get motion */
        bsm2->apply(substracted_image, substracted_image);

        /* if motion was detected save image */
        if (motion_detected())
            image_save();

        /* show result if test mode */
        images_show();

        /* wait "frame_delay" needed for capture frames from webcam */
        cv::waitKey(frame_delay);
    }
}

int Webcam::capture_frame(cv::Mat &frame)
{
    if (!is_work_correctly())
        return 1;

    return (int)webcam->read(frame);
}

int Webcam::images_create(const cv::Mat &frame)
{
    image = frame.clone();
#ifdef WEBCAM_FLIP
    cv::flip(image, image, 0);
#endif
    substracted_image = image.clone();
    return 0;
}

#ifdef WEBCAM_TEST
void Webcam::windows_create(void)
{
    cv::namedWindow(real_window_name);
    cv::namedWindow(move_window_name);
}
#else
void Webcam::windows_create(void)
{

}
#endif

#ifdef WEBCAM_TEST
void Webcam::images_show(void)
{
    cv::imshow(real_window_name, image);
    cv::imshow(move_window_name, substracted_image);
}
#else
void Webcam::images_show(void)
{

}
#endif

void Webcam::image_save(void)
{
    cv::imwrite(file, image);
}

bool Webcam::motion_detected(void)
{
    return cv::countNonZero(substracted_image) > MOVE_TRESHOLD(substracted_image);
}