LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := cxcore
LOCAL_C_INCLUDES := \
        $(LOCAL_PATH)/cxcore/include 
LOCAL_CFLAGS := $(LOCAL_C_INCLUDES:%=-I%)
LOCAL_LDLIBS := -L$(SYSROOT)/usr/lib -ldl

LOCAL_SRC_FILES := \
        cxcore/src/cxalloc.cpp \
        cxcore/src/cxarithm.cpp \
        cxcore/src/cxarray.cpp \
        cxcore/src/cxcmp.cpp \
        cxcore/src/cxconvert.cpp \
        cxcore/src/cxcopy.cpp \
        cxcore/src/cxdatastructs.cpp \
        cxcore/src/cxdrawing.cpp \
        cxcore/src/cxdxt.cpp \
        cxcore/src/cxerror.cpp \
        cxcore/src/cximage.cpp \
        cxcore/src/cxjacobieigens.cpp \
        cxcore/src/cxlogic.cpp \
        cxcore/src/cxlut.cpp \
        cxcore/src/cxmathfuncs.cpp \
        cxcore/src/cxmatmul.cpp \
        cxcore/src/cxmatrix.cpp \
        cxcore/src/cxmean.cpp \
        cxcore/src/cxmeansdv.cpp \
        cxcore/src/cxminmaxloc.cpp \
        cxcore/src/cxnorm.cpp \
        cxcore/src/cxouttext.cpp \
        cxcore/src/cxpersistence.cpp \
        cxcore/src/cxprecomp.cpp \
        cxcore/src/cxrand.cpp \
        cxcore/src/cxsumpixels.cpp \
        cxcore/src/cxsvd.cpp \
        cxcore/src/cxswitcher.cpp \
        cxcore/src/cxtables.cpp \
        cxcore/src/cxutils.cpp

include $(BUILD_STATIC_LIBRARY)


include $(CLEAR_VARS)

LOCAL_MODULE    := cv
LOCAL_C_INCLUDES := \
        $(LOCAL_PATH)/cxcore/include \
        $(LOCAL_PATH)/cxcore/src \
        $(LOCAL_PATH)/cv/include 
LOCAL_CFLAGS := $(LOCAL_C_INCLUDES:%=-I%)
LOCAL_LDLIBS := -L$(SYSROOT)/usr/lib -ldl

LOCAL_SRC_FILES := \
        cv/src/cvaccum.cpp \
        cv/src/cvadapthresh.cpp \
        cv/src/cvapprox.cpp \
        cv/src/cvcalccontrasthistogram.cpp \
        cv/src/cvcalcimagehomography.cpp \
        cv/src/cvcalibinit.cpp \
        cv/src/cvcalibration.cpp \
        cv/src/cvcamshift.cpp \
        cv/src/cvcanny.cpp \
        cv/src/cvcolor.cpp \
        cv/src/cvcondens.cpp \
        cv/src/cvcontours.cpp \
        cv/src/cvcontourtree.cpp \
        cv/src/cvconvhull.cpp \
        cv/src/cvcorner.cpp \
        cv/src/cvcornersubpix.cpp \
        cv/src/cvderiv.cpp \
        cv/src/cvdistransform.cpp \
        cv/src/cvdominants.cpp \
        cv/src/cvemd.cpp \
        cv/src/cvfeatureselect.cpp \
        cv/src/cvfilter.cpp \
        cv/src/cvfloodfill.cpp \
        cv/src/cvfundam.cpp \
        cv/src/cvgeometry.cpp \
        cv/src/cvhaar.cpp \
        cv/src/cvhistogram.cpp \
        cv/src/cvhough.cpp \
        cv/src/cvimgwarp.cpp \
        cv/src/cvinpaint.cpp \
        cv/src/cvkalman.cpp \
        cv/src/cvlinefit.cpp \
        cv/src/cvlkpyramid.cpp \
        cv/src/cvmatchcontours.cpp \
        cv/src/cvmoments.cpp \
        cv/src/cvmorph.cpp \
        cv/src/cvmotempl.cpp \
        cv/src/cvoptflowbm.cpp \
        cv/src/cvoptflowhs.cpp \
        cv/src/cvoptflowlk.cpp \
        cv/src/cvpgh.cpp \
        cv/src/cvposit.cpp \
        cv/src/cvprecomp.cpp \
        cv/src/cvpyramids.cpp \
        cv/src/cvpyrsegmentation.cpp \
        cv/src/cvrotcalipers.cpp \
        cv/src/cvsamplers.cpp \
        cv/src/cvsegmentation.cpp \
        cv/src/cvshapedescr.cpp \
        cv/src/cvsmooth.cpp \
        cv/src/cvsnakes.cpp \
        cv/src/cvstereobm.cpp \
        cv/src/cvstereogc.cpp \
        cv/src/cvsubdivision2d.cpp \
        cv/src/cvsumpixels.cpp \
        cv/src/cvsurf.cpp \
        cv/src/cvswitcher.cpp \
        cv/src/cvtables.cpp \
        cv/src/cvtemplmatch.cpp \
        cv/src/cvthresh.cpp \
        cv/src/cvundistort.cpp \
        cv/src/cvutils.cpp \

include $(BUILD_STATIC_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE    := opencv
LOCAL_C_INCLUDES := \
	$(LOCAL_PATH)/cxcore/include \
        $(LOCAL_PATH)/cv/include \
LOCAL_CFLAGS := $(LOCAL_C_INCLUDES:%=-I%)
LOCAL_LDLIBS := -L$(SYSROOT)/usr/lib -ldl -llog \
                -L$(TARGET_OUT) -lcxcore -lcv


LOCAL_SRC_FILES := cvjni.cpp


LOCAL_STATIC_LIBRARIES := cxcore cv

include $(BUILD_SHARED_LIBRARY)
