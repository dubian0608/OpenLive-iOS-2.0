//
//  MainViewController.swift
//  OpenLive-iOS-2.0
//
//  Created by ZhangJi on 26/07/2017.
//  Copyright © 2017 ZhangJi. All rights reserved.
//

import UIKit

class MainViewController: UIViewController {

    @IBOutlet var roomNameTextField: UITextField!
    
    fileprivate var videoProfile = AgoraRtcVideoProfile._VideoProfile_360P
    
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        guard let segueId = segue.identifier else {
            return
        }
        
        switch segueId {
        case "ShowSettings":
            let settingViewController = segue.destination as! SettingViewController
            settingViewController.videoProfile = videoProfile
            settingViewController.delegate = self
        case "ShowLiveRoom":
            let liveRoomViewController = segue.destination as! LiveRoomViewController
            liveRoomViewController.roomName = roomNameTextField.text
            liveRoomViewController.vodeoProfile = videoProfile
            if let role = sender {
                liveRoomViewController.clientRoel = role as! AgoraRtcClientRole
            }
        default:
            break
        }
    }
    
    @IBAction func tapJoinChannel(_ sender: UIButton) {
        let sheet = UIAlertController(title: "join channel as", message: nil, preferredStyle: .actionSheet)
        let broadcast = UIAlertAction(title: "Broadcast", style: .default) { (_) in
            self.join(withRole: .clientRole_Broadcaster)
        }
        let audience = UIAlertAction(title: "Audience", style: .default) { (_) in
            self.join(withRole: .clientRole_Audience)
        }
        let cancel = UIAlertAction(title: "Cancel", style: .cancel, handler: nil)
        sheet.addAction(broadcast)
        sheet.addAction(audience)
        sheet.addAction(cancel)
        present(sheet, animated: true, completion: nil)
        
    }

}

private extension MainViewController {
    func join(withRole role: AgoraRtcClientRole) {
        performSegue(withIdentifier: "ShowLiveRoom", sender: role)
    }
}

extension MainViewController: SettingViewControllerDelegate {
    func SettingProfile(_ SettingViewController: SettingViewController, didSelectProfile profile: AgoraRtcVideoProfile) {
        videoProfile = profile
        dismiss(animated: true, completion: nil)
    }
}
