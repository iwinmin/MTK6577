/* Copyright Statement:
 *
 * This software/firmware and related documentation ("MediaTek Software") are
 * protected under relevant copyright laws. The information contained herein is
 * confidential and proprietary to MediaTek Inc. and/or its licensors. Without
 * the prior written permission of MediaTek inc. and/or its licensors, any
 * reproduction, modification, use or disclosure of MediaTek Software, and
 * information contained herein, in whole or in part, shall be strictly
 * prohibited.
 * 
 * MediaTek Inc. (C) 2010. All rights reserved.
 * 
 * BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 * THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
 * RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO RECEIVER
 * ON AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL
 * WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR
 * NONINFRINGEMENT. NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH
 * RESPECT TO THE SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY,
 * INCORPORATED IN, OR SUPPLIED WITH THE MEDIATEK SOFTWARE, AND RECEIVER AGREES
 * TO LOOK ONLY TO SUCH THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO.
 * RECEIVER EXPRESSLY ACKNOWLEDGES THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO
 * OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES CONTAINED IN MEDIATEK
 * SOFTWARE. MEDIATEK SHALL ALSO NOT BE RESPONSIBLE FOR ANY MEDIATEK SOFTWARE
 * RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR
 * STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S
 * ENTIRE AND CUMULATIVE LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE
 * RELEASED HEREUNDER WILL BE, AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE
 * MEDIATEK SOFTWARE AT ISSUE, OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE
 * CHARGE PAID BY RECEIVER TO MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
 *
 * The following software/firmware and/or related documentation ("MediaTek
 * Software") have been modified by MediaTek Inc. All revisions are subject to
 * any receiver's applicable license agreements with MediaTek Inc.
 */

#ifndef FLV_PARSER_H_
#define FLV_PARSER_H_

#include <media/stagefright/MediaExtractor.h>
#include <media/stagefright/MediaBuffer.h>
#include <utils/Vector.h>
#include <utils/threads.h>

#include <cutils/log.h>
#undef LOG_TAG
#define LOG_TAG "FlvParser"






//common

#define ASCII_A  41
#define ASCII_a  61

typedef enum
{
    FLV_SEEK_FROM_CUR,
    FLV_SEEK_FROM_SET,
    FLV_SEEK_FROM_END,
}FLV_SEEK_FLAG;

typedef enum
{
    FLV_ERROR = 0,
    FLV_OK = 1,
    FLV_FILE_EOF = 2,
    FLV_FILE_OPEN_ERR = 3,
    FLV_FILE_READ_ERR = 4,
    FLV_ERR_NO_MEMORY = 5,
    FLV_ERROR_UNKNOWN = 6,
    
}FLV_ERROR_TYPE;


typedef enum {
    FLV_AMF_V3_TYPE_UNDEFINED      = 0x00,
    FLV_AMF_V3_TYPE_NULL           = 0x01,
    FLV_AMF_V3_TYPE_FALSE          = 0x02,
    FLV_AMF_V3_TYPE_TRUE           = 0x03,
    FLV_AMF_V3_TYPE_INT            = 0x05,
    FLV_AMF_V3_TYPE_DOUBLE         = 0x06,
    FLV_AMF_V3_TYPE_STRING         = 0x07,
    FLV_AMF_V3_TYPE_XML_DOC        = 0x08,
    FLV_AMF_V3_TYPE_DATE           = 0x09,
    FLV_AMF_V3_TYPE_ARRAY          = 0x0a,
    FLV_AMF_V3_TYPE_XML            = 0x0b,
    FLV_AMF_V3_TYPE_BYTE_ARRAY     = 0x0c,
} FLV_AMF_V3_TYPE;

//flv use V0
typedef enum {
    FLV_AMF_V0_TYPE_NUMBER      = 0x00,
    FLV_AMF_V0_TYPE_BOOL        = 0x01,
    FLV_AMF_V0_TYPE_STRING      = 0x02,
    FLV_AMF_V0_TYPE_OBJECT      = 0x03,
    FLV_AMF_V0_TYPE_MOVIECLIP   = 0x04,
    FLV_AMF_V0_TYPE_NULL        = 0x05,
    FLV_AMF_V0_TYPE_UNDEFINED   = 0x06,
    FLV_AMF_V0_TYPE_REFERENCE   = 0x07,
    FLV_AMF_V0_TYPE_MIXED_ARRAY = 0x08,
    FLV_AMF_V0_TYPE_OBJECT_END  = 0x09,
    FLV_AMF_V0_TYPE_ARRAY       = 0x0a,
    FLV_AMF_V0_TYPE_DATE        = 0x0b,
    FLV_AMF_V0_TYPE_LONG_STRING = 0x0c,
    FLV_AMF_V0_TYPE_UNSUPPORTED = 0x0d,
} FLV_AMF_V0_TYPE;

#define FLV_AMF_END_OF_OBJECT 0x000009


#define FLV_AMF_TYPE_LEN  1
#define FLV_AMF_STRING_SIZE_LEN 2
#define FLV_AMF_NUMBER_SIZE_LEN 8

//FLV Tag info 
typedef enum{
    FLV_TAG_TYPE_AUDIO = 0x08,
    FLV_TAG_TYPE_VIDEO = 0x09,
    FLV_TAG_TYPE_META  = 0x12,

}FLV_TAG_TYPE;

#define FLV_FILE_DEADER_SIZE         9
#define FLV_TAG_PREV_SIZE            4
#define FLV_TAG_HEADER_SIZE          15
#define FLV_TAG_TYPE_SIZE            1
#define FLV_TAG_DATA_SIZE            3
#define FLV_TAG_TS_SIZE              4
#define FLV_TAG_STREAM_ID_SIZE       3
#define FLV_HAS_VIDEO_BITMASK        0x01
#define FLV_HAS_AUDIO_BITMASK        0x04


//aduio tag

#define FLV_ADUIO_CODEC_TYPE_OFFSET 4
#define FLV_ADUIO_SAMPLE_RATE_OFFSET 2
#define FLV_ADUIO_SAMPLE_SIZE_OFFSET 1
#define FLV_ADUIO_SAMPLE_TYPE_OFFSET 0

#define FLV_ADUIO_CODEC_TYPE_BITMASK 0xF0
#define FLV_ADUIO_SAMPLE_RATE_BITMASK 0x0C
#define FLV_ADUIO_SAMPLE_SIZE_BITMASK 0x02
#define FLV_ADUIO_SAMPLE_TYPE_BITMASK 0x01

typedef enum{
        
    FLV_AUDIO_CODEC_ID_PCM                   = 0  ,
    FLV_AUDIO_CODEC_ID_ADPCM                 = 1  ,
    FLV_AUDIO_CODEC_ID_MP3                   = 2  ,
    FLV_AUDIO_CODEC_ID_PCM_LE                = 3  ,
    FLV_AUDIO_CODEC_ID_NELLYMOSER_16KHZ_MONO = 4  ,
    FLV_AUDIO_CODEC_ID_NELLYMOSER_8KHZ_MONO  = 5  ,
    FLV_AUDIO_CODEC_ID_NELLYMOSER            = 6  ,
    FLV_AUDIO_CODEC_ID_G711_ALAW             = 7  ,
    FLV_AUDIO_CODEC_ID_G711_MLAW             = 8  ,
    FLV_AUDIO_CODEC_ID_RESERVED              = 9  ,
    FLV_AUDIO_CODEC_ID_AAC                   = 10 ,
    FLV_AUDIO_CODEC_ID_SPEEX                 = 11 ,
    FLV_AUDIO_CODEC_ID_MP3_8K                = 14 ,
    FLV_AUDIO_CODEC_ID_DEVICE                = 15 ,
    FLV_AUDIO_CODEC_ID_UNKHNOWN              = 0XFF ,

}FLV_AUDIO_CODEC_ID;

typedef enum{
    FLV_AUDIO_SAMPLE_RATE_55 = 0 << FLV_ADUIO_SAMPLE_RATE_OFFSET,
    FLV_AUDIO_SAMPLE_RATE_11 = 1 << FLV_ADUIO_SAMPLE_RATE_OFFSET,  
    FLV_AUDIO_SAMPLE_RATE_22 = 2 << FLV_ADUIO_SAMPLE_RATE_OFFSET,
    FLV_AUDIO_SAMPLE_RATE_44 = 3 << FLV_ADUIO_SAMPLE_RATE_OFFSET

}FLV_AUDIO_SAMPLE_RATE;


typedef enum{
    FLV_AUDIO_SAMPLE_SIZE_0 = 0 << FLV_ADUIO_SAMPLE_SIZE_OFFSET,
    FLV_AUDIO_SAMPLE_SIZE_1 = 1 << FLV_ADUIO_SAMPLE_SIZE_OFFSET,

}FLV_AUDIO_SAMPLE_SIZE;


typedef enum{
    FLV_AUDIO_SAMPLE_TYEP_MOMO  = 0 << FLV_ADUIO_SAMPLE_TYPE_OFFSET,
    FLV_AUDIO_SAMPLE_SIZE_STEREO = 1 << FLV_ADUIO_SAMPLE_TYPE_OFFSET,
}FLV_AUDIO_SAMPLE_TYPE;


//video tag

#define FLV_VIDEO_FRAME_TYPE_OFFSET 4
#define FLV_VIDEO_CODEC_ID_OFFSET 0

#define FLV_VIDEO_FRAME_TYPE_BITMASK  0xf0
#define FLV_VIDEO_CODEC_ID_BITMASK    0x0f


typedef enum{
    FLV_VIDEO_FRAME_TYPE_KEY           = 1 << FLV_VIDEO_FRAME_TYPE_OFFSET,
    FLV_VIDEO_FRAME_TYPE_INTER_AVC     = 2 << FLV_VIDEO_FRAME_TYPE_OFFSET,
    FLV_VIDEO_FRAME_TYPE_INTER_H263    = 3 << FLV_VIDEO_FRAME_TYPE_OFFSET,
    FLV_VIDEO_FRAME_TYPE_KEY_RESERVED  = 4 << FLV_VIDEO_FRAME_TYPE_OFFSET,
    FLV_VIDEO_FRAME_TYPE_INFO_CMD      = 5 << FLV_VIDEO_FRAME_TYPE_OFFSET,

}FLV_VIDEO_FRAME_TYPE;


typedef enum{
    
    FLV_VIDEO_CODEC_ID_H263          = 2 ,
    FLV_VIDEO_CODEC_ID_SCREEN_VIDEO  = 3 ,
    FLV_VIDEO_CODEC_ID_VP6           = 4 ,
    FLV_VIDEO_CODEC_ID_VP6_ALPH      = 5 ,
    FLV_VIDEO_CODEC_ID_SCREEN2_VIDEO = 6 ,
    FLV_VIDEO_CODEC_ID_AVC           = 7 ,   
    FLV_VIDEO_CODEC_ID_UNKHNOWN      =0xFF,
}FLV_VIDEO_CODEC_ID;

typedef enum{
    
    FLV_VIDEO_AVC_PACKET_TYPE_CONFIG     = 0 ,
    FLV_VIDEO_AVC_PACKET_TYPE_NALS       = 1 ,
    FLV_VIDEO_AVC_PACKET_TYPE_UNKHNOWN   =0xFF,
}FLV_VIDEO_AVC_PACKET_TYPE;

typedef enum{
    
    FLV_AUDIO_AAC_PACKET_TYPE_CONFIG     = 0 ,
    FLV_AUDIO_AAC_PACKET_TYPE_NALS       = 1 ,
    FLV_AUDIO_AAC_PACKET_TYPE_UNKHNOWN   =0xFF,
}FLV_AUDIO_AAC_PACKET_TYPE;


#define FLV_VIDEO_AVC_TAG_CT_OFFSET        2 
#define FLV_VIDEO_AVC_TAG_DATA_OFFSET      5 
#define FLV_VIDEO_AVC_TAG_NAL_SIZE_OFFSET  4
#define FLV_VIDEO_AVC_TAG_DATA_RAW_OFFSET  5+FLV_VIDEO_AVC_TAG_NAL_SIZE_OFFSET  //4byte for nal len

#define FLV_VIDEO_S263_TAG_DATA_RAW_OFFSET  1

#define FLV_AUDIO_MP3_TAG_DATA_RAW_OFFSET   1
#define FLV_AUDIO_PCM_TAG_DATA_RAW_OFFSET   1
#define FLV_AUDIO_AAC_TAG_DATA_RAW_OFFSET   2


//file structure

#define FLV_SEEK_ENTRY_MAX_ENTRIES 2048 
#define FLV_SEEK_MAX_TIME_GRANULARITY 15000  //ms
#define FLV_SEEK_MIN_TIME_GRANULARITY 500  //ms

#define FLV_BS_BUFFER_SIZE  1024*1000


typedef struct 
{
    uint64_t ulTime;
    uint64_t ulOffset;
}flv_seek_table_entry;

typedef struct 
{
    flv_seek_table_entry*         pEntry;
    uint32_t                      MaxEntries;
    uint32_t                      SetEntries;
    uint64_t                      LastTime;
    uint64_t                      RangeTime;
    uint64_t                      TimeGranularity;
}flv_seek_table;

typedef struct
{
   uint32_t prv_tag_size;
   uint8_t  tag_type;
   uint32_t tag_data_size;
   uint64_t tag_ts;
   uint8_t  streamId;
}flv_tag_header_info;


typedef struct{
    flv_tag_header_info tag_header;
    uint32_t tag_data_offset;
    uint8_t* tag_data;
}flv_tag_str;




typedef struct  {
    
    double audio_codec_id;
    double audio_data_rate;
    double audio_delay;
    double audio_sample_rate;
    double audio_sample_size;
    double stereo;
    bool   can_seek_to_end;
    double creation_date;
    double duration; //ms
    double file_size;
    double frame_rate;
    double width;
    double height;
    double video_codec_id;
    double video_data_rate;
    double last_time_ts;
    double last_keyframe_ts;
    uint64_t fileposcnt;
    uint64_t fileposidx;
    uint64_t* filepositions; 
    uint64_t timescnt;
    uint64_t timesidx;
    uint64_t* times; 
    
}flv_meta_str;


typedef struct
{
        /* read function, returns -1 on error, 0 on EOF and read bytes
         * otherwise */
        uint32_t (*read)(void* source, void *buffer, uint32_t size);

        /* write function, returns -1 on error, 0 on EOF and written
         * bytes otherwise */
        uint32_t (*write)(void* source, void *buffer, uint32_t size);

        /* seek function, seeks to offset from beginning of the file,

         * returns -1 on error, 0 on EOF */
        uint64_t (*seek)(void* source, uint64_t offset,FLV_SEEK_FLAG flag);

        /* opaque data pointer passed to each of the stream handling
         * callbacks */
        void *source;
}flv_iostream_str;



typedef struct  {
        uint64_t  cur_file_offset;
        uint64_t  cur_tag;

        uint8_t   version;
        uint8_t   hasVideo;
        uint8_t   hasAudio;
        uint8_t   hasMeta; 
        uint32_t  header_size ;

        uint32_t  hasSeekTable ;

        /* position (in bytes) of data and index objects */
        uint64_t   file_hdr_position;
        uint64_t   meta_tag_position;
        uint64_t   data_tag_position;

        uint64_t   file_size;     
        uint64_t   duration;
        uint64_t   preroll;
        
        flv_iostream_str mIoStream;
        flv_meta_str*   mMeta;
}flv_file_str;





//parser function 




typedef uint32_t (*flv_io_read_func_ptr)(void *aSource, void *aBuffer, uint32_t aSize);
typedef uint32_t (*flv_io_write_func_ptr)(void *aSource, void *aBuffer, uint32_t aSize);
typedef uint64_t (*flv_io_seek_func_ptr)(void *aSource, uint64_t aOffset,FLV_SEEK_FLAG flag);


class flvParser
{
public:

        flvParser(void* source, flv_io_read_func_ptr read, flv_io_write_func_ptr write, flv_io_seek_func_ptr seek);

        ~flvParser();        

        flv_file_str *flv_open_file(flv_iostream_str *pStream);
        
        void flv_close();

        FLV_ERROR_TYPE IsflvFile();

        FLV_ERROR_TYPE ParseflvFile();        

        flv_tag_str *flv_tag_create();
        
        void flv_tag_destroy(flv_tag_str *tag);

        FLV_ERROR_TYPE flv_read_a_tag(flv_tag_str *tag);
            
        int64_t flv_seek_to_msec(int64_t msec);
        
        void flv_metadata_destroy(flv_meta_str *metadata);
        
        uint8_t flv_get_stream_count();
        
       // flv_stream_str *flv_get_stream(uint8_t track);
        
        bool flv_is_seekable();

        bool flv_has_video();

        bool flv_has_audio();

        FLV_VIDEO_CODEC_ID flv_get_videocodecid();

        FLV_AUDIO_CODEC_ID flv_get_audiocodecid();

        void flv_get_resolution(uint32_t* width,uint32_t* height);
        
        uint64_t flv_get_file_size();
        
        uint64_t flv_get_creation_date();
        
        uint64_t flv_get_duration();
        
        uint32_t flv_get_max_bitrate();

        uint32_t flv_get_tag_size();
        
        flv_meta_str* flv_get_meta();
        

private:
        FLV_ERROR_TYPE flv_parse_amf_obj(uint8_t* amf_data,uint32_t amf_data_len,uint32_t* offset,char* key,flv_meta_str* metaInfo,uint32_t depth);
        
        FLV_ERROR_TYPE flv_parse_onMetaData(flv_tag_str* pMeta_tag,flv_meta_str* metaInfo);
        
        FLV_ERROR_TYPE flv_read_tag_header(flv_tag_header_info *tag_header);

        FLV_ERROR_TYPE flv_parse_script();

	    FLV_ERROR_TYPE flv_parse_header();

        FLV_ERROR_TYPE flv_read_tag_header(uint8_t* out);

        //FLV_ERROR_TYPE flv_parse_codec_config_data();
        
        //seek target time is 
        FLV_ERROR_TYPE flv_setup_seektable();
        FLV_ERROR_TYPE flv_search_all_seek_tables(int64_t seekTimeMs,int64_t foundTimeMs,uint64_t foundVideoTagPos);
        int64_t flv_update_seek_table(flv_tag_str* cur_tag);
        void flv_dump_seektable();

     
protected:


        //flv context structure 
        flv_file_str *    mfile;
        flv_seek_table *  mSeekTable;
        FLV_ERROR_TYPE mError;
        
};



#endif // FLV_PARSER_H_

















