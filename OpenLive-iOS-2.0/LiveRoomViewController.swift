//
//  LiveRoomViewController.swift
//  OpenLive-iOS-2.0
//
//  Created by ZhangJi on 31/07/2017.
//  Copyright © 2017 ZhangJi. All rights reserved.
//

import UIKit

class LiveRoomViewController: UIViewController {

    @IBOutlet weak var remoteView: UIView!
    @IBOutlet weak var buttonStackView: UIStackView!
    @IBOutlet weak var muteVidoeButton: UIButton!
    @IBOutlet weak var muteAudioButton: UIButton!
    @IBOutlet weak var roomNameLabel: UILabel!
    
    var roomName: String!
    var clientRoel: AgoraRtcClientRole!
    var vodeoProfile: AgoraRtcVideoProfile!
    
    //MARK: - Publisher
    var publisher: AgoraLivePublisher?
    
    //MARK: - engine & session view
    var rtcEngine: AgoraRtcEngineKit!
    fileprivate var isBroadcast: Bool {
        return clientRoel == .clientRole_Broadcaster
    }
    
    fileprivate var isAudioMuted = false {
        didSet {
            rtcEngine.muteLocalAudioStream(isAudioMuted)
            muteAudioButton.setImage(isAudioMuted ? #imageLiteral(resourceName: "btn_mute_cancel") : #imageLiteral(resourceName: "btn_mute"), for: .normal)
        }
    }
    
    fileprivate var isVideoMuted = false {
        didSet {
            rtcEngine.muteLocalVideoStream(isVideoMuted)
            muteVidoeButton.setImage(isVideoMuted ? #imageLiteral(resourceName: "btn_ join") : #imageLiteral(resourceName: "btn_join_cancel"), for: .normal)
        }
    }
    
    fileprivate var videoSessions = [VideoSession]() {
        didSet {
            guard remoteView != nil  else {
                return
            }
            updateinterface(withAnimation: true)
        }
    }
    
    fileprivate var fullSession: VideoSession? {
        didSet {
            if fullSession != oldValue && remoteView != nil {
                updateinterface(withAnimation: true)
            }
        }
    }
    
    fileprivate let viewLayouter = VideoViewLayouter()
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        roomNameLabel.text = roomName
        updateButton()
        
        loadAgoraKit()
        
    }
    
    //MARK: - uesr action
    
    @IBAction func tapMuteVideoButton(_ sender: UIButton) {
        isVideoMuted = !isVideoMuted
    }
    
    @IBAction func tapSwitchCameraButton(_ sender: UIButton) {
        rtcEngine.switchCamera()
    }
    
    @IBAction func tapMuteAudioButton(_ sender: UIButton) {
        isAudioMuted = !isAudioMuted
    }
    
    @IBAction func tapHandupButton(_ sender: UIButton) {
        self.leaveChannel()
    }
    
    @IBAction func onDoubleTapped(_ sender: UITapGestureRecognizer) {
        if fullSession == nil {
            if let tappedSession = viewLayouter.responseSession(of: sender, inSessions: videoSessions, inContainerView: remoteView) {
                fullSession = tappedSession
            }
        } else {
            fullSession = nil
        }
    }
}

extension LiveRoomViewController {
    func updateButton() {
        buttonStackView.isHidden = !isBroadcast
    }
    
    func setIdleTimeActive(_ active: Bool) {
        UIApplication.shared.isIdleTimerDisabled = !active
    }
    
    func alter(alter: String) {
        guard !alter.isEmpty else {
            return
        }
        
        let alterController = UIAlertController(title: nil, message: alter, preferredStyle: .alert)
        let OkAction = UIAlertAction(title: "OK", style: .default, handler: nil)
        alterController.addAction(OkAction)
        
        present(alterController, animated: true, completion: nil)
    }
}

//MARK: - Channel Action

extension LiveRoomViewController {
    func loadAgoraKit() {
        rtcEngine = AgoraRtcEngineKit.sharedEngine(withAppId: KeyCenter.AppId, delegate: self)
        rtcEngine.setChannelProfile(.channelProfile_LiveBroadcasting)
        rtcEngine.enableDualStreamMode(true)
        rtcEngine.enableVideo()
        rtcEngine.setVideoProfile(vodeoProfile, swapWidthAndHeight: true)
        rtcEngine.setClientRole(clientRoel, withKey: nil)
        
        if isBroadcast{
            rtcEngine.startPreview()
//            isVideoMuted = false
//            isAudioMuted = false
        }
        
//        addLocalSession()
        
        let code = rtcEngine.joinChannel(byKey: nil, channelName: roomName, info: nil, uid: 0, joinSuccess: nil)
        if code == 0{
            setIdleTimeActive(false)
            rtcEngine.setEnableSpeakerphone(true)
        }else {
            DispatchQueue.main.async(execute: {
                self.alter(alter: "Join channel failed: \(code)")
            })
        }
        
    }
    
    func leaveChannel() {
        setIdleTimeActive(true)
        rtcEngine.setupLocalVideo(nil)
        rtcEngine.leaveChannel(nil)
        if isBroadcast {
            rtcEngine.stopPreview()
        }
        for session in videoSessions {
            session.hostingView.removeFromSuperview()
        }
        videoSessions.removeAll()
        
        navigationController?.popViewController(animated: true)
    }
}

//MARK: - Video Session Setup

extension LiveRoomViewController {
    func addLocalSession() {
        let localSession  = VideoSession.localSession()
        videoSessions.append(localSession)
        rtcEngine.setupLocalVideo(localSession.canvas)
    }
    
    func fetchSession(ofUid uid: Int64) -> VideoSession? {
        for session in videoSessions {
            if session.uid == uid {
                return session
            }
        }
        return nil
    }
    
    func videoSession(ofUid uid: Int64) -> VideoSession {
        if let fetchSession = fetchSession(ofUid: uid) {
            return fetchSession
        }else {
            let newSession = VideoSession(uid: uid)
            videoSessions.append(newSession)
            return newSession
        }
    }
    
    func updateInterface() {
        var displaySessions = videoSessions
        if !isBroadcast && !displaySessions.isEmpty{
            displaySessions.removeFirst()
        }
        viewLayouter.layout(sessions: displaySessions, fullSession: fullSession, inContainer: remoteView)
        setStreamType(forSessions: videoSessions, fullSession: fullSession)
    }
    
    func updateinterface(withAnimation animation: Bool) {
        if animation {
            UIView.animate(withDuration: 0.3, animations: { 
                self.updateInterface()
                self.view.layoutIfNeeded()
            })
        } else {
            updateInterface()
        }
    }
    
    func setStreamType(forSessions sessions: [VideoSession], fullSession: VideoSession?) {
        if let fullSession = fullSession {
            for session in sessions {
                rtcEngine.setRemoteVideoStream(UInt(session.uid), type: (session == fullSession ? .videoStream_High : .videoStream_Low))
            }
        } else {
            for session in sessions {
                rtcEngine.setRemoteVideoStream(UInt(session.uid), type: .videoStream_High)
            }
        }
    }
}

//MAKR: - Publisher Antion

extension LiveRoomViewController {
//    func publisherTest() {
//        if let publisher = publisher {
//            <#statements#>
//        }
//        publisher = AgoraLivePublisher.init(liveKit: rtcEngine)
//    }
}

//MARK: - AgoraRtcEngine Delegate

extension LiveRoomViewController: AgoraRtcEngineDelegate {
    func rtcEngine(_ engine: AgoraRtcEngineKit!, didJoinChannel channel: String!, withUid uid: UInt, elapsed: Int) {
        print("Uid :\(uid)")
    }
    
    func rtcEngine(_ engine: AgoraRtcEngineKit!, didJoinedOfUid uid: UInt, elapsed: Int) {
        print("Uid :\(uid)")
    }
    
    func rtcEngine(_ engine: AgoraRtcEngineKit!, firstRemoteVideoDecodedOfUid uid: UInt, size: CGSize, elapsed: Int) {
        let userSession = videoSession(ofUid: Int64(uid))
        rtcEngine.setupRemoteVideo(userSession.canvas)
    }
    
    func rtcEngine(_ engine: AgoraRtcEngineKit!, firstLocalVideoFrameWith size: CGSize, elapsed: Int) {
        if let _ = videoSessions.first {
            updateinterface(withAnimation: false)
        }
    }
    
    func rtcEngine(_ engine: AgoraRtcEngineKit!, didOfflineOfUid uid: UInt, reason: AgoraRtcUserOfflineReason) {
        var indexToDelete: Int?
        for (index, session) in videoSessions.enumerated() {
            if session.uid == Int64(uid) {
                indexToDelete = index
            }
        }
        
        if let indexToDelete = indexToDelete {
            let deletedSession = videoSessions.remove(at: indexToDelete)
            deletedSession.hostingView.removeFromSuperview()
            
            if deletedSession == fullSession {
                fullSession = nil
            }
        }
    }
}

























