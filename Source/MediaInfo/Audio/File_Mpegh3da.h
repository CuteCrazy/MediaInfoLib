/*  Copyright (c) MediaArea.net SARL. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license that can
 *  be found in the License.html file in the root of the source tree.
 */

//---------------------------------------------------------------------------
#ifndef MediaInfo_File_Mpegh3daH
#define MediaInfo_File_Mpegh3daH
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#include "MediaInfo/Tag/File__Tags.h"
#include "MediaInfo/Audio/File_Usac.h"
#include "MediaInfo/Audio/File_Aac.h"
//---------------------------------------------------------------------------

namespace MediaInfoLib
{

//***************************************************************************
// Class File_Mpegh3da
//***************************************************************************

struct speaker_info
{
    Aac_OutputChannel CICPspeakerIdx;
    int16u AzimuthAngle;
    bool AzimuthDirection;
    int16u ElevationAngle;
    bool ElevationDirection;
    bool isLFE;
};

class File_Mpegh3da : public File_Usac
{
public :
    //In
    bool   MustParse_mhaC;
    bool   MustParse_mpegh3daFrame;

    //Constructor/Destructor
    File_Mpegh3da();

private :
    //Info

    struct speaker_layout
    {
        int32u numSpeakers;
        vector<Aac_OutputChannel> CICPspeakerIdxs;
        vector<speaker_info> SpeakersInfo;

        int8u ChannelLayout;
        speaker_layout() :
            numSpeakers(0),
            ChannelLayout(0)
        {};
    };

    speaker_layout referenceLayout;
    int8u mpegh3daProfileLevelIndication;
    int32u usacSamplingFrequency;
    int8u coreSbrFrameLengthIndex;

    //Streams management
    void Streams_Fill();
    void Streams_Finish();

    //Buffer - Global
    void Read_Buffer_Continue();

    //Buffer - Per element
    void Header_Parse();
    void Data_Parse();

    //Elements
    void Sync();
    void mpegh3daConfig();
    void SpeakerConfig3d(speaker_layout& Layout);
    void mpegh3daFlexibleSpeakerConfig(speaker_layout& Layout);
    void mpegh3daSpeakerDescription(speaker_info& SpeakerInfo, bool angularPrecision);
    void mpegh3daFrame();
    void mhaC();

    //Helpers
    void Streams_Fill_ChannelLayout(const string& Prefix, const speaker_layout& Layout, int8u speakerLayoutType=0);
};

} //NameSpace

#endif
