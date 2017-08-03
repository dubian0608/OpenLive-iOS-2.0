//
//  AgoraLiveKit.h
//  AgoraLiveKit
//
//  Created by Sting Feng on 2015-8-11.
//  Copyright (c) 2015 Agora. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AgoraLiveKit.h"

#if TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
typedef UIView VIEW_CLASS;
typedef UIColor COLOR_CLASS;

#elif TARGET_OS_MAC
#import <AppKit/AppKit.h>
typedef NSView VIEW_CLASS;
typedef NSColor COLOR_CLASS;
#endif

typedef NS_ENUM(NSInteger, AgoraLiveVideoStreamType) {
    AgoraLiveVideoStreamHigh = 0,
    AgoraLiveVideoStreamLow = 1,
};


@class AgoraLiveSubscriber;

@protocol AgoraLiveSubscriberDelegate <NSObject>
@optional

// subscriber kit相关
- (void)liveSubcriber: (AgoraLiveSubscriber *_Nonnull)subscriber didPublishedByUid:(NSUInteger)uid streamType:(AgoraLiveMediaType) type;


- (void)liveSubcriber: (AgoraLiveSubscriber *_Nonnull)subscriber didUnpublishedByUid:(NSUInteger)uid streamType:(AgoraLiveMediaType) type;

// rtmp流被发布、remove
// 没有通知


// video


/**
 *  Event of the first frame of remote user is rendering on the screen.
 *
 *  @param kit     The live kit
 *  @param uid     The remote user id
 *  @param size    The size of video stream
 *  @param elapsed The elapsed time(ms) from the beginning of the session.
 */
- (void)liveSubcriber:(AgoraLiveSubscriber *_Nonnull)subscriber firstRemoteVideoFrameOfUid:(NSUInteger)uid size:(CGSize)size elapsed:(NSInteger)elapsed;

/**
 *  Event of video size changed for local or remote user
 *
 *  @param kit     The live kit
 *  @param uid     The user id
 *  @param size    The new size of video
 *  @param rotation  The new rotate of video
 */
- (void)liveSubcriber:(AgoraLiveSubscriber *_Nonnull)subscriber videoSizeChangedOfUid:(NSUInteger)uid size:(CGSize)size rotation:(NSInteger)rotation;
@end


__attribute__((visibility("default"))) @interface AgoraLiveSubscriber: NSObject // AgoraLiveSubscriber

-(instancetype _Nonnull)initWithLiveKit:(AgoraLiveKit * _Nonnull)kit;

-(void)setSubscriberDelegate:(_Nullable id<AgoraLiveSubscriberDelegate>) delegate;

- (void)subscribeByUid:(NSUInteger)uid
             mediaType:(AgoraLiveMediaType)mediaType
                  view:(VIEW_CLASS *_Nullable)view
            renderMode:(AgoraLiveRenderMode)mode
             videoType:(AgoraLiveVideoStreamType)videoType;

-(void)unsubcribeByUid:(NSUInteger)uid;

@end
