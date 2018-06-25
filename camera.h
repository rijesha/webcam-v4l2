/** Small C++ wrapper around V4L example code to access the webcam
**/

#include <string>
#include <iostream>
#include <memory> // unique_ptr

using namespace std;

struct buffer {
      void   *data;
      size_t  size;
};

struct Image {
      unsigned char   *data; // RGB888 <=> RGB24
      size_t          width;
      size_t          height;
      size_t          size; // width * height * 3
};


class Camera {

public:
    Camera(const std::string& device = "/dev/video0", 
           int width = 640, 
           int height = 480,
           bool grayscale = false);

    ~Camera();

    /** Captures and returns a frame from the Camera.
     *
     * The returned object contains a field 'data' with the image data in RGB888
     * format (ie, RGB24), as well as 'width', 'height' and 'size' (equal to
     * width * height * 3)
     *
     * This call blocks until a frame is available or until the provided
     * timeout (in seconds). 
     *
     * Throws a runtime_error if the timeout is reached.
     */
    const Image& captureFrame(int timeout = 15);

private:
    void init_mmap();

    void open_device();
    void close_device();

    void init_device();
    void uninit_device();

    void start_capturing();
    void stop_capturing();

    bool read_frame();

    void set_fmt();
    void set_crop();

    std::string device;
    int fd;
    bool grayscale;

    Image frame;
    struct buffer          *buffers;
    unsigned int     n_buffers;

    size_t xres, yres;
    size_t stride;

    bool force_format = true;
};




