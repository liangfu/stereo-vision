/**
 * @file   svrectify.cpp
 * @author Liangfu Chen <chenclf@gmail.com>
 * @date   Tue Feb  7 22:50:35 2012
 * 
 * @brief  
 * 
 * 
 */


#include "svrectify.h"


void fractorizePPM(const CvArr * P, CvArr * A, CvArr * R, CvArr * t)
{
	double Q[3][3];
	CvMat _Q = cvMat(3, 3, CV_64F, Q);
	// cvInvert(P, _Q);
}

int
svStereoRectifyUncalibrated2(
    const CvMat* _points1, const CvMat* _points2,
    const CvMat* F0, CvSize imgSize, CvMat* _H1, CvMat* _H2, double threshold )
{

	CV_FUNCNAME( "svStereoCalcHomographiesFromF" );
	__BEGIN__;
	
	
	
	
	__END__;
	
	return 1;
}









// CV_IMPL
int
svStereoRectifyUncalibrated(
    const CvMat* _points1, const CvMat* _points2,
    const CvMat* F0, CvSize imgSize, CvMat* _H1, CvMat* _H2, double threshold )
{
    int result = 0;
    CvMat* _m1 = 0;
    CvMat* _m2 = 0;
    CvMat* _lines1 = 0;
    CvMat* _lines2 = 0;

    CV_FUNCNAME( "svStereoCalcHomographiesFromF" );

    __BEGIN__;

    int i, j, npoints;
    double cx, cy;
    double u[9], v[9], w[9], f[9], h1[9], h2[9], h0[9], e2[3];
    CvMat E2 = cvMat( 3, 1, CV_64F, e2 );
    CvMat U = cvMat( 3, 3, CV_64F, u );
    CvMat V = cvMat( 3, 3, CV_64F, v );
    CvMat W = cvMat( 3, 3, CV_64F, w );
    CvMat F = cvMat( 3, 3, CV_64F, f );
    CvMat H1 = cvMat( 3, 3, CV_64F, h1 );
    CvMat H2 = cvMat( 3, 3, CV_64F, h2 );
    CvMat H0 = cvMat( 3, 3, CV_64F, h0 );

    CvPoint2D64f* m1;
    CvPoint2D64f* m2;
    CvPoint3D64f* lines1;
    CvPoint3D64f* lines2;

    CV_ASSERT( CV_IS_MAT(_points1) && CV_IS_MAT(_points2) &&
        (_points1->rows == 1 || _points1->cols == 1) &&
        (_points2->rows == 1 || _points2->cols == 1) &&
        CV_ARE_SIZES_EQ(_points1, _points2) );

    npoints = _points1->rows * _points1->cols * CV_MAT_CN(_points1->type) / 2;

    _m1 = cvCreateMat( _points1->rows, _points1->cols, CV_64FC(CV_MAT_CN(_points1->type)) );
    _m2 = cvCreateMat( _points2->rows, _points2->cols, CV_64FC(CV_MAT_CN(_points2->type)) );
    _lines1 = cvCreateMat( 1, npoints, CV_64FC3 );
    _lines2 = cvCreateMat( 1, npoints, CV_64FC3 );

    cvConvert( F0, &F );

    cvSVD( (CvMat*)&F, &W, &U, &V, CV_SVD_U_T + CV_SVD_V_T );
    W.data.db[8] = 0.;
    cvGEMM( &U, &W, 1, 0, 0, &W, CV_GEMM_A_T );
    cvMatMul( &W, &V, &F );

    cx = cvRound( (imgSize.width-1)*0.5 );
    cy = cvRound( (imgSize.height-1)*0.5 );

    cvZero( _H1 );
    cvZero( _H2 );

    cvConvert( _points1, _m1 );
    cvConvert( _points2, _m2 );
    cvReshape( _m1, _m1, 2, 1 );
    cvReshape( _m1, _m1, 2, 1 );

    m1 = (CvPoint2D64f*)_m1->data.ptr;
    m2 = (CvPoint2D64f*)_m2->data.ptr;
    lines1 = (CvPoint3D64f*)_lines1->data.ptr;
    lines2 = (CvPoint3D64f*)_lines2->data.ptr;

    if( threshold > 0 )
    {
        cvComputeCorrespondEpilines( _m1, 1, &F, _lines1 );
        cvComputeCorrespondEpilines( _m2, 2, &F, _lines2 );

        // measure distance from points to the corresponding epilines, mark outliers
        for( i = j = 0; i < npoints; i++ )
        {
            if( fabs(m1[i].x*lines2[i].x +
                     m1[i].y*lines2[i].y +
                     lines2[i].z) <= threshold &&
                fabs(m2[i].x*lines1[i].x +
                     m2[i].y*lines1[i].y +
                     lines1[i].z) <= threshold )
            {
                if( j > i )
                {
                    m1[j] = m1[i];
                    m2[j] = m2[i];
                }
                j++;
            }
        }

        npoints = j;
        if( npoints == 0 )
            EXIT;
    }

    {
    _m1->cols = _m2->cols = npoints;
    memcpy( E2.data.db, U.data.db + 6, sizeof(e2));
    cvScale( &E2, &E2, e2[2] > 0 ? 1 : -1 );

    double t[] =
    {
        1, 0, -cx,
        0, 1, -cy,
        0, 0, 1
    };
    CvMat T = cvMat(3, 3, CV_64F, t);
    cvMatMul( &T, &E2, &E2 );

    int mirror = e2[0] < 0;
    double d = MAX(sqrt(e2[0]*e2[0] + e2[1]*e2[1]),DBL_EPSILON);
    double alpha = e2[0]/d;
    double beta = e2[1]/d;
    double r[] =
    {
        alpha, beta, 0,
        -beta, alpha, 0,
        0, 0, 1
    };
    CvMat R = cvMat(3, 3, CV_64F, r);
    cvMatMul( &R, &T, &T );
    cvMatMul( &R, &E2, &E2 );
    double invf = fabs(e2[2]) < 1e-6*fabs(e2[0]) ? 0 : -e2[2]/e2[0];
    double k[] =
    {
        1, 0, 0,
        0, 1, 0,
        invf, 0, 1
    };
    CvMat K = cvMat(3, 3, CV_64F, k);
    cvMatMul( &K, &T, &H2 );
    cvMatMul( &K, &E2, &E2 );

    double it[] =
    {
        1, 0, cx,
        0, 1, cy,
        0, 0, 1
    };
    CvMat iT = cvMat( 3, 3, CV_64F, it );
    cvMatMul( &iT, &H2, &H2 );

    memcpy( E2.data.db, U.data.db + 6, sizeof(e2));
    cvScale( &E2, &E2, e2[2] > 0 ? 1 : -1 );

    double e2_x[] =
    {
        0, -e2[2], e2[1],
       e2[2], 0, -e2[0],
       -e2[1], e2[0], 0
    };
    double e2_111[] =
    {
        e2[0], e2[0], e2[0],
        e2[1], e2[1], e2[1],
        e2[2], e2[2], e2[2],
    };
    CvMat E2_x = cvMat(3, 3, CV_64F, e2_x);
    CvMat E2_111 = cvMat(3, 3, CV_64F, e2_111);
    cvMatMulAdd(&E2_x, &F, &E2_111, &H0 );
    cvMatMul(&H2, &H0, &H0);
    CvMat E1=cvMat(3, 1, CV_64F, V.data.db+6);
    cvMatMul(&H0, &E1, &E1);

    cvPerspectiveTransform( _m1, _m1, &H0 );
    cvPerspectiveTransform( _m2, _m2, &H2 );
    CvMat A = cvMat( 1, npoints, CV_64FC3, lines1 ), BxBy, B;
    double a[9], atb[3], x[3];
    CvMat AtA = cvMat( 3, 3, CV_64F, a );
    CvMat AtB = cvMat( 3, 1, CV_64F, atb );
    CvMat X = cvMat( 3, 1, CV_64F, x );
    cvConvertPointsHomogeneous( _m1, &A );
    cvReshape( &A, &A, 1, npoints );
    cvReshape( _m2, &BxBy, 1, npoints );
    cvGetCol( &BxBy, &B, 0 );
    cvGEMM( &A, &A, 1, 0, 0, &AtA, CV_GEMM_A_T );
    cvGEMM( &A, &B, 1, 0, 0, &AtB, CV_GEMM_A_T );
    cvSolve( &AtA, &AtB, &X, CV_SVD_SYM );

    double ha[] =
    {
        x[0], x[1], x[2],
        0, 1, 0,
        0, 0, 1
    };
    CvMat Ha = cvMat(3, 3, CV_64F, ha);
    cvMatMul( &Ha, &H0, &H1 );
    cvPerspectiveTransform( _m1, _m1, &Ha );

    if( mirror )
    {
        double mm[] = { -1, 0, cx*2, 0, -1, cy*2, 0, 0, 1 };
        CvMat MM = cvMat(3, 3, CV_64F, mm);
        cvMatMul( &MM, &H1, &H1 );
        cvMatMul( &MM, &H2, &H2 );
    }

    cvConvert( &H1, _H1 );
    cvConvert( &H2, _H2 );

    result = 1;
    }

    __END__;

    cvReleaseMat( &_m1 );
    cvReleaseMat( &_m2 );
    cvReleaseMat( &_lines1 );
    cvReleaseMat( &_lines2 );

    return result;
}

