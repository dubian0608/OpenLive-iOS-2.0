//
//  VideoSession.swift
//  OpenLive-iOS-2.0
//
//  Created by ZhangJi on 31/07/2017.
//  Copyright © 2017 ZhangJi. All rights reserved.
//

import UIKit

class VideoSession: NSObject {
    var uid: Int64 = 0
    var hostingView: UIView!
    var canvas: AgoraRtcVideoCanvas!
    
    init(uid: Int64) {
        self.uid = uid
        
        hostingView = UIView(frame: CGRect(x: 0, y: 0, width: 100, height: 100))
        hostingView.translatesAutoresizingMaskIntoConstraints = false
        
        canvas = AgoraRtcVideoCanvas()
        canvas.uid = UInt(uid)
        canvas.view = hostingView
        canvas.renderMode = .render_Hidden
    }
}

extension VideoSession {
    static func localSession() -> VideoSession {
        return VideoSession(uid: 0)
    }
}
