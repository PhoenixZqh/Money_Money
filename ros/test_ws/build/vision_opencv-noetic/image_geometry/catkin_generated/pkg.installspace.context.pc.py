# generated from catkin/cmake/template/pkg.context.pc.in
CATKIN_PACKAGE_PREFIX = ""
PROJECT_PKG_CONFIG_INCLUDE_DIRS = "${prefix}/include;/usr/local/opencv-4.5.1/include/opencv4".split(';') if "${prefix}/include;/usr/local/opencv-4.5.1/include/opencv4" != "" else []
PROJECT_CATKIN_DEPENDS = "sensor_msgs".replace(';', ' ')
PKG_CONFIG_LIBRARIES_WITH_PREFIX = "-limage_geometry;/usr/local/opencv-4.5.1/lib/libopencv_calib3d.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_core.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_dnn.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_features2d.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_flann.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_gapi.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_highgui.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_imgcodecs.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_imgproc.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_ml.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_objdetect.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_photo.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_stitching.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_video.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_videoio.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_alphamat.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_aruco.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_bgsegm.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_bioinspired.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_ccalib.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_cudaarithm.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_cudabgsegm.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_cudacodec.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_cudafeatures2d.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_cudafilters.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_cudaimgproc.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_cudalegacy.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_cudaobjdetect.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_cudaoptflow.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_cudastereo.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_cudawarping.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_cudev.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_cvv.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_datasets.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_dnn_objdetect.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_dnn_superres.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_dpm.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_face.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_freetype.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_fuzzy.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_hdf.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_hfs.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_img_hash.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_intensity_transform.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_line_descriptor.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_mcc.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_optflow.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_phase_unwrapping.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_plot.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_quality.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_rapid.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_reg.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_rgbd.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_saliency.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_sfm.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_shape.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_stereo.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_structured_light.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_superres.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_surface_matching.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_text.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_tracking.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_videostab.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_viz.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_xfeatures2d.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_ximgproc.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_xobjdetect.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_xphoto.so.4.5.1".split(';') if "-limage_geometry;/usr/local/opencv-4.5.1/lib/libopencv_calib3d.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_core.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_dnn.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_features2d.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_flann.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_gapi.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_highgui.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_imgcodecs.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_imgproc.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_ml.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_objdetect.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_photo.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_stitching.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_video.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_videoio.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_alphamat.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_aruco.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_bgsegm.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_bioinspired.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_ccalib.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_cudaarithm.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_cudabgsegm.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_cudacodec.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_cudafeatures2d.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_cudafilters.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_cudaimgproc.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_cudalegacy.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_cudaobjdetect.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_cudaoptflow.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_cudastereo.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_cudawarping.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_cudev.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_cvv.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_datasets.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_dnn_objdetect.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_dnn_superres.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_dpm.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_face.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_freetype.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_fuzzy.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_hdf.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_hfs.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_img_hash.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_intensity_transform.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_line_descriptor.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_mcc.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_optflow.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_phase_unwrapping.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_plot.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_quality.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_rapid.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_reg.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_rgbd.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_saliency.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_sfm.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_shape.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_stereo.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_structured_light.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_superres.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_surface_matching.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_text.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_tracking.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_videostab.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_viz.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_xfeatures2d.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_ximgproc.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_xobjdetect.so.4.5.1;/usr/local/opencv-4.5.1/lib/libopencv_xphoto.so.4.5.1" != "" else []
PROJECT_NAME = "image_geometry"
PROJECT_SPACE_DIR = "/home/zqh/PhoenixZ/Money_Money/ros/test_ws/install"
PROJECT_VERSION = "1.16.2"
