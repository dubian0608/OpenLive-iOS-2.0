//
//  ProfileCell.swift
//  OpenLive-iOS-2.0
//
//  Created by ZhangJi on 30/07/2017.
//  Copyright © 2017 ZhangJi. All rights reserved.
//

import UIKit

class ProfileCell: UITableViewCell {

    @IBOutlet var resLabel: UILabel!
    @IBOutlet var frameLabel: UILabel!
    @IBOutlet var bitRateLabel: UILabel!
    
    func update(withProfile profile: AgoraRtcVideoProfile, isSelected: Bool) {
        resLabel.text = profile.resolution()
        frameLabel.text = profile.fps()
        bitRateLabel.text = profile.bitRate()
        backgroundColor = isSelected ? UIColor(red: 0, green: 0, blue: 0.5, alpha: 0.3) : UIColor.white
    }
}

private extension AgoraRtcVideoProfile {
    func resolution() -> String? {
        switch self {
        case ._VideoProfile_120P: return "160×120"
        case ._VideoProfile_180P: return "320×180"
        case ._VideoProfile_240P: return "320×240"
        case ._VideoProfile_360P: return "640×360"
        case ._VideoProfile_480P: return "640×480"
        case ._VideoProfile_720P: return "1280×720"
        default: return nil
        }
    }
    
    func fps() -> String? {
        return "15"
    }
    
    func bitRate() -> String? {
        switch self {
        case ._VideoProfile_120P: return "65"
        case ._VideoProfile_180P: return "140"
        case ._VideoProfile_240P: return "200"
        case ._VideoProfile_360P: return "400"
        case ._VideoProfile_480P: return "500"
        case ._VideoProfile_720P: return "1130"
        default: return nil
        }
    }

}

