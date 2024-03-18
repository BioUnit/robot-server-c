#include "myvideo.h"

#define ULTRAFAST 1
#define ZEROLATENCY 4

GstElement *pipeline;
GstElement *src;
GstElement *videoconvert;
GstElement *encoder;
GstElement *capsfilter;
GstElement *sink;
GstCaps *caps;


int create_video_pipeline(void){
   gst_init(NULL, NULL);
   pipeline = gst_pipeline_new("pipeline");

   src = gst_element_factory_make("v4l2src", "autovideosrc");
   if(!src){
      g_printerr("Failed to create src\r\n");
      return -1;
   } else {
      g_print("Source: OK\n");
   }
   g_object_set(src, "device", "/dev/video1", NULL);

   videoconvert = gst_element_factory_make("videoconvert", "videoconvert");
   if(!videoconvert){
      g_printerr("Failed to create videoconvert\n");
      return -1;
   } else {
      g_print("Videoconvert: OK\n");
   }

   capsfilter = gst_element_factory_make("capsfilter", "capsfilter");
   if(!capsfilter){
      g_printerr("Failed to create capsfilter\n");
      return -1;
   } else {
      g_print("Capsfilter: OK\n");
   }
   caps = gst_caps_from_string("video/x-raw,format=I420,width=640,height=480");
   g_object_set(capsfilter, "caps", caps, NULL);
   gst_caps_unref(caps);

   encoder = gst_element_factory_make("x264enc", "my_encoder");
   if(!encoder){
      g_printerr("Failed to create encoder\n");
      return -1;
   } else {
      g_print("Encoder: OK\n");
   }
   g_object_set(encoder, "bitrate", 2000, "speed-preset", ULTRAFAST, "tune", ZEROLATENCY,"threads", 2, "noise-reduction", 3,  NULL);

   sink = gst_element_factory_make("udpsink", "udpsink");
   if(!sink){
      g_printerr("Failed to create sink\n");
      return -1;
   } else {
      g_print("Sink: OK\n");
   }
   g_object_set(sink, "host", "192.168.0.105", "port", 5000, NULL);

   return 1;
}

void start_video_pipeline(void){
   gst_bin_add_many(GST_BIN(pipeline), src, videoconvert, capsfilter, encoder, sink, NULL);
   gst_element_link_many(src, videoconvert, capsfilter, encoder, sink, NULL);

   gst_element_set_state(pipeline, GST_STATE_PLAYING);
   g_print("Pipeline playing\n");
}
