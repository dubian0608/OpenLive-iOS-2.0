//
//  AgoraLiveKit.h
//  AgoraLiveKit
//
//  Created by Sting Feng on 2015-8-11.
//  Copyright (c) 2015 Agora. All rights reserved.
//

#import <Foundation/Foundation.h>
//#import "AgoraRtcEngineKit.h"
#import <AgoraRtcEngineKit/AgoraRtcEngineKit.h>

#if TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
typedef UIView VIEW_CLASS;
typedef UIColor COLOR_CLASS;

#elif TARGET_OS_MAC
#import <AppKit/AppKit.h>
typedef NSView VIEW_CLASS;
typedef NSColor COLOR_CLASS;
#endif

typedef NS_ENUM(NSInteger, AgoraLiveWarningCode) {
    AgoraLiveWarningCodeInvalidView = 8,
    AgoraLiveWarningCodeInitVideo = 16,
    AgoraLiveWarningCodePending = 20,
    AgoraLiveWarningCodeNoAvailableChannel = 103,
    AgoraLiveWarningCodeLookupChannelTimeout = 104,
    AgoraLiveWarningCodeLookupChannelRejected = 105,
    AgoraLiveWarningCodeOpenChannelTimeout = 106,
    AgoraLiveWarningCodeOpenChannelRejected = 107,
    AgoraLiveWarningCodeSwitchLiveVideoTimeout = 111,
    // sdk:vos, callmanager, peermanager: 100~1000
    AgoraLiveWarningCodeSetClientRoleTimeout = 118,
    AgoraLiveWarningCodeSetClientRoleNotAuthorized = 119,
    AgoraLiveWarningCodeAudioMixingOpenError = 701,

    AgoraLiveWarningCodeAdmRuntimePlayoutWarning = 1014,
    AgoraLiveWarningCodeAdmRuntimeRecordingWarning = 1016,
    AgoraLiveWarningCodeAdmRecordAudioSilence = 1019,
    AgoraLiveWarningCodeAdmPlaybackMalfunction = 1020,
    AgoraLiveWarningCodeAdmRecordMalfunction = 1021,
    AgoraLiveWarningCodeAdmInterruption = 1025,
    AgoraLiveWarningCodeApmHowling = 1051,
};

typedef NS_ENUM(NSInteger, AgoraLiveErrorCode) {
    AgoraLiveErrorCodeNoError = 0,
    AgoraLiveErrorCodeFailed = 1,
    AgoraLiveErrorCodeInvalidArgument = 2,
    AgoraLiveErrorCodeNotReady = 3,
    AgoraLiveErrorCodeNotSupported = 4,
    AgoraLiveErrorCodeRefused = 5,
    AgoraLiveErrorCodeBufferTooSmall = 6,
    AgoraLiveErrorCodeNotInitialized = 7,
    AgoraLiveErrorCodeNoPermission = 9,
    AgoraLiveErrorCodeTimedOut = 10,
    AgoraLiveErrorCodeCanceled = 11,
    AgoraLiveErrorCodeTooOften = 12,
    AgoraLiveErrorCodeBindSocket = 13,
    AgoraLiveErrorCodeNetDown = 14,
    AgoraLiveErrorCodeNoBufs = 15,
    AgoraLiveErrorCodeJoinChannelRejected = 17,
    AgoraLiveErrorCodeLeaveChannelRejected = 18,
    AgoraLiveErrorCodeAlreadyInUse = 19,

    AgoraLiveErrorCodeInvalidAppId = 101,
    AgoraLiveErrorCodeInvalidChannelName = 102,
    AgoraLiveErrorCodeChannelKeyExpired = 109,
    AgoraLiveErrorCodeInvalidChannelKey = 110,
    AgoraLiveErrorCodeConnectionInterrupted = 111, // only used in web sdk
    AgoraLiveErrorCodeConnectionLost = 112, // only used in web sdk
    AgoraLiveErrorCodeNotInChannel = 113,
    AgoraLiveErrorCodeSizeTooLarge = 114,
    AgoraLiveErrorCodeBitrateLimit = 115,
    AgoraLiveErrorCodeTooManyDataStreams = 116,
    AgoraLiveErrorCodeDecryptionFailed = 120,
    
    AgoraLiveErrorCodeLoadMediaEngine = 1001,
    AgoraLiveErrorCodeStartCall = 1002,
    AgoraLiveErrorCodeStartCamera = 1003,
    AgoraLiveErrorCodeStartVideoRender = 1004,
    AgoraLiveErrorCodeAdmGeneralError = 1005,
    AgoraLiveErrorCodeAdmJavaResource = 1006,
    AgoraLiveErrorCodeAdmSampleRate = 1007,
    AgoraLiveErrorCodeAdmInitPlayout = 1008,
    AgoraLiveErrorCodeAdmStartPlayout = 1009,
    AgoraLiveErrorCodeAdmStopPlayout = 1010,
    AgoraLiveErrorCodeAdmInitRecording = 1011,
    AgoraLiveErrorCodeAdmStartRecording = 1012,
    AgoraLiveErrorCodeAdmStopRecording = 1013,
    AgoraLiveErrorCodeAdmRuntimePlayoutError = 1015,
    AgoraLiveErrorCodeAdmRuntimeRecordingError = 1017,
    AgoraLiveErrorCodeAdmRecordAudioFailed = 1018,
    AgoraLiveErrorCodeAdmPlayAbnormalFrequency = 1020,
    AgoraLiveErrorCodeAdmRecordAbnormalFrequency = 1021,
    AgoraLiveErrorCodeAdmInitLoopback  = 1022,
    AgoraLiveErrorCodeAdmStartLoopback = 1023,
    // 1025, as warning for interruption of adm on ios
    // 1026, as warning for route change of adm on ios
    // VDM error code starts from 1500
    AgoraLiveErrorCodeVdmCameraNotAuthorized = 1501,

    // VCM error code starts from 1600
    AgoraLiveErrorCodeVcmUnknownError = 1600,
    AgoraLiveErrorCodeVcmEncoderInitError = 1601,
    AgoraLiveErrorCodeVcmEncoderEncodeError = 1602,
    AgoraLiveErrorCodeVcmEncoderSetError = 1603,
};

typedef NS_ENUM(NSUInteger, AgoraLiveQuality) {
    AgoraLiveQualityUnknown = 0,
    AgoraLiveQualityExcellent = 1,
    AgoraLiveQualityGood = 2,
    AgoraLiveQualityPoor = 3,
    AgoraLiveQualityBad = 4,
    AgoraLiveQualityVBad = 5,
    AgoraLiveQualityDown = 6,
};

typedef NS_ENUM(NSUInteger, AgoraLiveUserOfflineReason) {
    AgoraLiveUserOfflineReasonQuit = 0,
    AgoraLiveUserOfflineReasonDropped = 1,
    AgoraLiveUserOfflineReasonBecomeAudience = 2,
};

typedef NS_ENUM(NSInteger, AgoraLiveMediaType) {
    AgoraLiveMediaTypeNone = 0,
    AgoraLiveMediaTypeAudioOnly = 1,
    AgoraLiveMediaTypeVideoOnly = 2,
    AgoraLiveMediaTypeAudioAndVideo = 3,
};


typedef NS_ENUM(NSUInteger, AgoraLiveRenderMode) {
    /**
     Hidden(1): If the video size is different than that of the display window, crops the borders of the video (if the video is bigger) or stretch the video (if the video is smaller) to fit it in the window.
     */
    AgoraLiveRenderModeHidden = 1,
    
    /**
     AgoraLiveRenderModeFit(2): If the video size is different than that of the display window, resizes the video proportionally to fit the window.
     */
    AgoraLiveRenderModeFit = 2,
    
    /**
     AgoraLiveRenderModeAdaptive(3)：If both callers use the same screen orientation, i.e., both use vertical screens or both use horizontal screens, the AgoraLiveRenderModeHidden mode applies; if they use different screen orientations, i.e., one vertical and one horizontal, the AgoraLiveRenderModeFit mode applies.
     */
    AgoraLiveRenderModeAdaptive = 3,
};

typedef NS_ENUM(NSInteger, AgoraLiveEncryptionMode) {
    AgoraLiveEncryptionModeNone = 0,
    AgoraLiveEncryptionModeAES128XTS = 1,
    AgoraLiveEncryptionModeAES256XTS = 2,
    AgoraLiveEncryptionModeAES128ECB = 3,
};


__attribute__((visibility("default"))) @interface AgoraLiveChannelConfig: NSObject
@property (assign, nonatomic) BOOL videoEnabled;
@property (assign, nonatomic) AgoraLiveEncryptionMode encryptionMode;
@property (copy, nonatomic) NSString *_Nullable secret;
// @property (assign, nonatomic) BOOL hostInEnabled; 是否启用信令。默认每个SDK端Publish时都应该启用信令

+(AgoraLiveChannelConfig *_Nonnull) defaultConfig;
@end

__attribute__((visibility("default"))) @interface AgoraLiveStats: NSObject
@property (assign, nonatomic) NSInteger duration;
@property (assign, nonatomic) NSInteger txBytes;
@property (assign, nonatomic) NSInteger rxBytes;
@property (assign, nonatomic) NSInteger txAudioKBitrate;
@property (assign, nonatomic) NSInteger rxAudioKBitrate;
@property (assign, nonatomic) NSInteger txVideoKBitrate;
@property (assign, nonatomic) NSInteger rxVideoKBitrate;
@property (assign, nonatomic) NSInteger userCount;
@property (assign, nonatomic) double cpuAppUsage;
@property (assign, nonatomic) double cpuTotalUsage;
@end


@class AgoraLiveKit;
@class AgoraLiveSubscriber;
@class AgoraLivePublisher;

@protocol AgoraLiveDelegate <NSObject>
@optional

/**
 *  The warning occurred in SDK. The APP could igonre the warning, and the SDK could try to resume automically.
 *
 *  @param kit         The live kit
 *  @param warningCode The warning code
 */
- (void)liveKit:(AgoraLiveKit *_Nonnull)kit didOccurWarning:(AgoraLiveWarningCode)warningCode;

/**
 *  The error occurred in SDK. The SDK couldn't resume to normal state, and the app need to handle it.
 *
 *  @param kit       The live kit
 *  @param errorCode The error code
 */
- (void)liveKit:(AgoraLiveKit *_Nonnull)kit didOccurError:(AgoraLiveErrorCode)errorCode;

/**
 *  Event of the user joined the channel.
 *
 *  @param kit     The live kit
 *  @param channel The channel name
 *  @param uid     The remote user id
 *  @param elapsed The elapsed time (ms) from session beginning
 */
- (void)liveKit:(AgoraLiveKit *_Nonnull)kit didJoinChannel:(NSString *_Nonnull)channel withUid:(NSUInteger)uid elapsed:(NSInteger) elapsed;

/**
 *  The statistics of the call when leave channel
 *
 *  @param kit    The live kit
 */
- (void)liveKitDidLeaveChannel:(AgoraLiveKit *_Nonnull)kit;

/**
 *  Event of remote user joined
 *
 *  @param kit     The live kit
 *  @param uid     The remote user id
 *  @param elapsed The elapsed time(ms) from the beginning of the session.
 */
- (void)liveKit:(AgoraLiveKit *_Nonnull)kit didOnlineOfUid:(NSUInteger)uid elapsed:(NSInteger)elapsed;

/**
 *  Event of remote user offlined
 *
 *  @param kit    The live kit
 *  @param uid    The remote user id
 *  @param reason Reason of user offline, quit, drop or became audience
 */
- (void)liveKit:(AgoraLiveKit *_Nonnull)kit didOfflineOfUid:(NSUInteger)uid reason:(AgoraLiveUserOfflineReason)reason;

/**
 *  Event of the user rejoined the channel
 *
 *  @param kit     The live kit
 *  @param channel The channel name
 *  @param uid     The user id
 *  @param elapsed The elapsed time (ms) from session beginning
 */
- (void)liveKit:(AgoraLiveKit *_Nonnull)kit didRejoinChannel:(NSString *_Nonnull)channel withUid:(NSUInteger)uid elapsed:(NSInteger) elapsed;


// statistics

/**
 *  Statistics of rtc live kit status. Updated every two seconds.
 *
 *  @param kit    The live kit
 *  @param stats  The statistics of rtc status, including duration, sent bytes and received bytes
 */
- (void)liveKit:(AgoraLiveKit *_Nonnull)kit reportLiveStats:(AgoraLiveStats *_Nonnull)stats;
// network

/**
 *  Event of disconnected with server. This event is reported at the moment SDK loses connection with server.
 *  In the mean time SDK automatically tries to reconnect with the server until APP calls leaveChannel.
 *
 *  @param kit    The live kit
 */
- (void)liveKitConnectionDidInterrupted:(AgoraLiveKit *_Nonnull)kit;

/**
 *  Event of loss connection with server. This event is reported after the connection is interrupted and exceed the retry period (10 seconds by default).
 *  In the mean time SDK automatically tries to reconnect with the server until APP calls leaveChannel.
 *
 *  @param kit    The live kit
 */
- (void)liveKitConnectionDidLost:(AgoraLiveKit *_Nonnull)kit;

/**
 *  The network quality of local user.
 *
 *  @param kit     The live kit
 *  @param uid     The id of user
 *  @param txQuality The sending network quality
 *  @param rxQuality The receiving network quality
 */
- (void)liveKit:(AgoraLiveKit *_Nonnull)kit networkQuality:(NSUInteger)uid txQuality:(AgoraLiveQuality)txQuality rxQuality:(AgoraLiveQuality)rxQuality;


// 是否有必要？
/**
 *  Event of the first local frame starts rendering on the screen.
 *
 *  @param kit     The live kit
 *  @param size    The size of local video stream
 *  @param elapsed The elapsed time(ms) from the beginning of the session.
 */
- (void)liveKit:(AgoraLiveKit *_Nonnull)kit firstLocalVideoFrameWithSize:(CGSize)size elapsed:(NSInteger)elapsed;

@end


__attribute__((visibility("default"))) @interface AgoraLiveKit : NSObject

/**
*  Get the version of Agora SDK.
*
*  @return string, sdk version
*/
+ (NSString *_Nonnull)getSdkVersion;

/**
 *  Get the native handler of sdk Engine
 */
- (AgoraRtcEngineKit *_Nonnull)getRtcEngineKit;

/**
 *  Initializes the AgoraLiveKit object.
 *
 *  @param appId The appId is issued to the application developers by Agora.
 *
 *  @return an object of AgoraLiveKit class
 */
+ (instancetype _Nonnull)sharedLiveKitWithAppId:(NSString *_Nonnull)appId;

+ (void)destroy;

/**
 *  Description
 *
 *  @param delegate live delegate
 *
 */
- (void)setDelegate:(id<AgoraLiveDelegate> _Nullable) delegate;

/** BEGIN OF COMMON METHODS */

/**
 *  Create an open UDP socket to the AgoraLiveKit cloud service to join a channel.
    Users in the same channel can talk to each other with same vendor key.
    Users using different vendor keys cannot call each other.
    The method is asynchronous.
 *
 *  @param channelId       Joining in the same channel indicates those clients have entered in one room.
 *  @param channelKey        Channel key generated by APP using sign certificate.
 *  @param channelConfig     configration of channel
 *  @param uid               Optional, this argument is the unique ID for each member in one channel.
                             If set to 0, the SDK automatically allocates an ID, and the id could be gotten in didJoinChannel delegate.
 *
 *  @return 0 when executed successfully, and return negative value when failed.
 */
- (int)joinChannel:(NSString *_Nonnull)channelId
               key:(NSString *_Nullable)channelKey
            config:(AgoraLiveChannelConfig *_Nonnull)channelConfig
               uid:(NSUInteger)uid;

/**
 *  lets the user leave a channel, i.e., hanging up or exiting a call.
    After joining a channel, the user must call the leaveChannel method to end the call before joining another one.
    It is synchronous, i.e., it only returns until the call ends and all resources are released.
 *
 *  @return 0 if executed successfully, or return negative value if failed.
 */
- (int)leaveChannel;

/**
 *  start local video preview, while not sending data to server
 *
 *  @return 0 when this method is called successfully, or negative value when this method failed.
 */
- (int)startPreview:(VIEW_CLASS *_Nonnull)view
         renderMode:(AgoraLiveRenderMode)mode;

/**
 *  stop local video preview
 *
 *  @return 0 when this method is called successfully, or negative value when this method failed.
 */
- (int)stopPreview;

- (int)requestHostInToOwner:(NSUInteger)uid;

- (int)respondHostInToUser:(NSUInteger)uid;

- (int)inviteHostInToUser:(NSUInteger)uid;

- (int)replyHostInInvitationToOwner:(NSUInteger)uid;
@end
