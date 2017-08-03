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

typedef NS_ENUM(NSInteger, AgoraLiveVideoProfile) {
                                            // res       fps  kbps
    AgoraLiveVideoProfileInvalid = -1,
    AgoraLiveVideoProfile120P = 0,         // 160x120   15   65
#if TARGET_OS_IPHONE
	AgoraLiveVideoProfile120P_3 = 2,		// 120x120   15   50
    AgoraLiveVideoProfile180P = 10,		// 320x180   15   140
    AgoraLiveVideoProfile180P_3 = 12,		// 180x180   15   100
    AgoraLiveVideoProfile180P_4 = 13,		// 240x180   15   120
#endif
    AgoraLiveVideoProfile240P = 20,		// 320x240   15   200
#if TARGET_OS_IPHONE
    AgoraLiveVideoProfile240P_3 = 22,		// 240x240   15   140
    AgoraLiveVideoProfile240P_4 = 23,		// 424x240   15   220
#endif
    AgoraLiveVideoProfile360P = 30,		// 640x360   15   400
#if TARGET_OS_IPHONE
	AgoraLiveVideoProfile360P_3 = 32,		// 360x360   15   260
#endif
    AgoraLiveVideoProfile360P_4 = 33,		// 640x360   30   600
    AgoraLiveVideoProfile360P_6 = 35,		// 360x360   30   400
    AgoraLiveVideoProfile360P_7 = 36,		// 480x360   15   320
    AgoraLiveVideoProfile360P_8 = 37,		// 480x360   30   490
    AgoraLiveVideoProfile360P_9 = 38,      // 640x360   15   800
    AgoraLiveVideoProfile360P_10 = 39,     // 640x360   24   800
    AgoraLiveVideoProfile360P_11 = 100,    // 640x360   24   1000
    AgoraLiveVideoProfile480P = 40,		// 640x480   15   500
#if TARGET_OS_IPHONE
	AgoraLiveVideoProfile480P_3 = 42,		// 480x480   15   400
#endif
    AgoraLiveVideoProfile480P_4 = 43,		// 640x480   30   750
    AgoraLiveVideoProfile480P_6 = 45,		// 480x480   30   600
    AgoraLiveVideoProfile480P_8 = 47,		// 848x480   15   610
    AgoraLiveVideoProfile480P_9 = 48,		// 848x480   30   930
    AgoraLiveVideoProfile480P_10 = 49,		// 640x480   10   400
    AgoraLiveVideoProfile720P = 50,		// 1280x720  15   1130
    AgoraLiveVideoProfile720P_3 = 52,		// 1280x720  30   1710
    AgoraLiveVideoProfile720P_5 = 54,		// 960x720   15   910
    AgoraLiveVideoProfile720P_6 = 55,		// 960x720   30   1380
    AgoraLiveVideoProfile1080P = 60,		// 1920x1080 15   2080
    AgoraLiveVideoProfile1080P_3 = 62,		// 1920x1080 30   3150
    AgoraLiveVideoProfile1080P_5 = 64,		// 1920x1080 60   4780
    AgoraLiveVideoProfile1440P = 66,		// 2560x1440 30   4850
    AgoraLiveVideoProfile1440P_2 = 67,		// 2560x1440 60   7350
    AgoraLiveVideoProfile4K = 70,			// 3840x2160 30   8190
    AgoraLiveVideoProfile4K_3 = 72,		// 3840x2160 60   13500
    AgoraLiveVideoProfileDEFAULT = AgoraLiveVideoProfile360P,
};

__attribute__((visibility("default"))) @interface AgoraLiveTranscodingUser: NSObject
@property (assign, nonatomic) NSUInteger uid;
// 音频控制
@property (assign, nonatomic) CGRect rect;
@property (assign, nonatomic) NSInteger zOrder; //optional, [0, 100] //0 (default): bottom most, 100: top most
@property (assign, nonatomic) double alpha; //optional, [0, 1.0] where 0 denotes throughly transparent, 1.0 opaque
@property (assign, nonatomic) AgoraLiveRenderMode renderMode;

//+(AgoraLiveTranscodingUser *) defaultConfig
@end

__attribute__((visibility("default"))) @interface AgoraLiveTranscoding: NSObject
@property (assign, nonatomic) CGSize size;
@property (assign, nonatomic) NSInteger bitrate;
@property (assign, nonatomic) NSInteger framerate;
@property (assign, nonatomic) BOOL lowLatency;

@property (strong, nonatomic) COLOR_CLASS *_Nullable backgroundColor;
@property (copy, nonatomic) NSArray<AgoraLiveTranscodingUser *> *_Nullable transcodingUsers;
@property (copy, nonatomic) NSString *_Nullable transcodingExtraInfo;
@end


@class AgoraLivePublisher;

@protocol AgoraLivePublisherDelegate <NSObject>
@optional

-(void)publisher: (AgoraLivePublisher *_Nonnull)publisher didSubscribedByUid:(NSUInteger)uid mediaType:(AgoraLiveMediaType) type ;

-(void)publisher: (AgoraLivePublisher *_Nonnull)publisher didUnsubscribedByUid:(NSUInteger)uid;

@end


__attribute__((visibility("default"))) @interface AgoraLivePublisher: NSObject

@property (copy, nonatomic) NSString *_Nullable permissionKey;
@property (assign, nonatomic) AgoraLiveVideoProfile profile;

-(instancetype _Nonnull)initWithLiveKit:(AgoraLiveKit * _Nonnull)kit;

-(void)setPublisherDelegate:(id<AgoraLivePublisherDelegate> _Nullable) delegate;

-(void)setLiveTranscoding:(AgoraLiveTranscoding *_Nullable) transcoding;

-(void)setMediaType:(AgoraLiveMediaType)mediaType;

-(void)addStreamUrl:(NSString *_Nullable)url transcodingEnabled:(BOOL)transcodingEnabled;

-(void)removeStreamUrl:(NSString *_Nullable)url;

-(void)publish;

-(void)unpublish;

-(void)switchCamera;

//-(void)setExternalVideoSource:(AgoraLiveExteranalVideoSource *)source;
@end
