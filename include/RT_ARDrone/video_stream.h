#ifndef VIDEO_STREAM_H
#define VIDEO_STREAM_H


// ****************************************************************************
// ***
// ***
// *** RT_Ardrone - A basic library for interfacing the AR.Drone quadricopter
// ***
// *** Copyright (C)   Sebastien Druon ( sebastien.druon@univ-montp2.fr )
// ***
// *** This program is free software: you can redistribute it and/or modify
// *** it under the terms of the GNU General Public License as published by
// *** the Free Software Foundation, either version 3 of the License, or
// *** (at your option) any later version.
// ***
// *** This program is distributed in the hope that it will be useful,
// *** but WITHOUT ANY WARRANTY; without even the implied warranty of
// *** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// *** GNU General Public License for more details.
// *** 
// *** You should have received a copy of the GNU General Public License
// *** along with this program.  If not, see <http://www.gnu.org/licenses/>.
// ***
// ***
// ***
// ****************************************************************************

#include <pthread.h>
#include <netinet/in.h>

#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>

#include <RT_ARDrone/image.h>

#define VIDEO_PORT	5555

typedef struct {

	// socket stuff

	int 			socket ;
	struct hostent*		host ;		
	struct sockaddr_in	addr ;	

	// thread stuff

	pthread_t		thread ;
	pthread_mutex_t		mutex ;

	// H264 decoder

	AVCodec* 	pCodecH264 ; 
	AVCodecContext* pCodecCtxH264 ;
	AVDictionary* 	opts ;
	AVPacket 	packet ;

	AVFrame*	picture ;		// last picture captured. protected by mutex

	int 		bool_new_picture ;	// True if one picture was captured since last read
	
	// Conversion to RGB24

  	struct SwsContext* 	sws_ctx ;
	AVFrame* 	   	RGBPicture ;



} VideoStream ;

VideoStream* VideoStream_new ( const char* ip_addr ) ;
void VideoStream_free ( VideoStream* ) ;

void VideoStream_connect ( VideoStream* ) ;

void VideoStream_getRGB24Image( VideoStream*, RGB24Image* ) ;
void VideoStream_getYUV420Image( VideoStream*, YUV420Image* ) ;

#endif






