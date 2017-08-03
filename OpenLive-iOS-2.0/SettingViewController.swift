//
//  SettingViewController.swift
//  OpenLive-iOS-2.0
//
//  Created by ZhangJi on 30/07/2017.
//  Copyright © 2017 ZhangJi. All rights reserved.
//

import UIKit

protocol SettingViewControllerDelegate: NSObjectProtocol {
    func SettingProfile(_ SettingViewController: SettingViewController, didSelectProfile profile: AgoraRtcVideoProfile)
}

class SettingViewController: UIViewController {

    @IBOutlet weak var profileTableView: UITableView!
    
    var videoProfile: AgoraRtcVideoProfile! {
        didSet{
            profileTableView?.reloadData()
        }
    }
    
    weak var delegate: SettingViewControllerDelegate?
    
    fileprivate let profiles: [AgoraRtcVideoProfile] = AgoraRtcVideoProfile.list()

    @IBAction func doConfirmPressed(_ sender: UIButton) {
        //dismiss(animated: true, completion: nil)
        delegate?.SettingProfile(self, didSelectProfile: videoProfile)
    }
}

extension SettingViewController: UITableViewDataSource {
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return profiles.count
    }
    
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCell(withIdentifier: "ProfileCell", for: indexPath) as! ProfileCell
        let selectedProfile = profiles[(indexPath as NSIndexPath).row]
        cell.update(withProfile: selectedProfile, isSelected: (selectedProfile == videoProfile))
        
        return cell
    }
}

extension SettingViewController: UITableViewDelegate {
    func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        let selectedProfile = profiles[(indexPath as NSIndexPath).row]
        self.videoProfile = selectedProfile
    }
}

private extension AgoraRtcVideoProfile {
    static func list() -> [AgoraRtcVideoProfile] {
        return [._VideoProfile_120P,
                ._VideoProfile_180P,
                ._VideoProfile_240P,
                ._VideoProfile_360P,
                ._VideoProfile_480P,
                ._VideoProfile_720P]
    }
}
