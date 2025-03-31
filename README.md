# ZeroKeyUSB

**A portable, offline password manager for secure, cloud-free credential storage**

ZeroKeyUSB is more than just an offline password manager — it’s a portable, hardware-based vault that lets you securely carry your most sensitive credentials anywhere, without relying on apps, clouds, or internet access. Designed for professionals and teams who need to move fast and stay secure, it stores up to 64 encrypted credentials in secure EEPROM memory, protected by a PIN-based authentication system with signature verification.

With a crisp 128x32 OLED display and an intuitive capacitive touch interface, managing passwords is fast and frustration-free—even on the go. ZeroKeyUSB is powered via USB Type-C, requiring no batteries or charging, and is fully compatible with computers, smartphones, and any device that supports USB HID. Built to be water- and dust-resistant, it’s a durable, ultra-portable solution for anyone who values both security and convenience.

<a href="https://www.instagram.com/p/DFtAv4eNb4j/">
  <img src="https://github.com/Depbit-lab/Zerokey/blob/main/Pictures/instagram%20video.png" alt="Watch the video" width="200">
</a>




---

## Table of Contents

- [Overview](#overview)
- [Keep It Secret, Keep It Safe](#keep-it-secret-keep-it-safe)
- [Features & Specifications](#features--specifications)
- [Frequently Asked Questions](#frequently-asked-questions)
- [Contributing](#contributing)
- [License](#license)

---

## Overview

In a world where online password managers store and sync your credentials on cloud services and third-party platforms, ZeroKeyUSB takes a radically different approach. It never connects to the internet, never installs software on your devices, and never leaves a digital trace. Instead, your credentials are stored securely in encrypted hardware memory and are only accessible through physical interaction using a PIN-protected, tamper-resistant system.

ZeroKeyUSB is ideal for:
- **Individuals** seeking a private and portable alternative to mainstream password managers.
- **IT technicians** who work across multiple systems.
- **Crypto enthusiasts** and security-focused professionals in need of a reliable offline vault.

Moreover, unlike most electronic devices, ZeroKeyUSB has no components with a limited lifespan. It draws power directly from any USB-C port—eliminating the need for batteries and ensuring longevity.

---

## Keep It Secret, Keep It Safe

Online password managers have made it easy to store and sync credentials—but at the cost of entrusting your most sensitive data to cloud services and third-party platforms. Recent high-profile breaches have shown just how vulnerable these solutions can be. Even strong encryption can’t protect your data if the platform itself is compromised.

ZeroKeyUSB takes a different approach:  
- It **never connects** to the internet.  
- It **never installs** software on your devices.  
- It **never leaves a digital trace**.

Your credentials remain securely stored in encrypted hardware memory, accessible only through direct, physical interaction. This robust, offline system is designed for those with higher-than-average security needs.

---

## Features & Specifications

### Key Features
- **Offline Operation:**  
  No internet connection or third-party software required. Works on any computer or smartphone that supports USB HID.
  
- **Secure Storage:**  
  Stores up to 64 credentials in secure EEPROM memory with AES-128 encryption.
  
- **User-Friendly Interface:**  
  - 128x32 OLED display for clear visual feedback.  
  - Five capacitive touch buttons for intuitive, offline navigation.
  
- **Robust Authentication:**  
  Protected by a PIN-based authentication system with signature verification.

- **Universal Compatibility:**  
  Acts as a standard USB HID input device across multiple operating systems and devices.

### Technical Specifications
- **Chip:** SAM D21 Arm Cortex-M0+
- **Display:** 128x32 OLED screen
- **Input:** Five capacitive touch buttons
- **Encryption:** AES-128
- **Power:** USB Type-C bus-powered (no battery)
- **Durability:** Water-, dust-, and tamper-resistant
- **Dimensions:** 55mm × 15mm × 4mm (2.165 in × 0.591 in × 0.157 in)
- **Weight:** 5g

---

## Frequently Asked Questions

### Do I need to install any software to use ZeroKeyUSB?
No. ZeroKeyUSB works out of the box on any computer or smartphone that supports USB HID input. No drivers, apps, or extensions are required.

### How do I navigate the interface?
Navigation is done using five capacitive touch buttons placed beside the OLED screen. The interface is simple, icon-based, and fully offline.

### How do I back up my credentials?
You can back up and manage your stored credentials through a web interface provided with the device. This tool runs entirely offline and can be opened locally on your computer—no installation or internet connection required. It allows you to add, reorder, and export encrypted backups securely.

### What happens if I lose the device?
If your device is lost or stolen, your credentials remain safe. ZeroKeyUSB is protected by a PIN and uses AES-128 encryption. Without the correct PIN, stored data is inaccessible and cannot be extracted.

### Does it support two-factor authentication (2FA)?
Not at the moment. ZeroKeyUSB is focused on secure, offline credential storage and does not natively support 2FA protocols like TOTP or FIDO. However, since the firmware is fully open source, developers are welcome to extend its functionality—including adding 2FA or other custom features.

### Is the firmware open source?
Yes. Firmware, schematics, and design files are all released under the MIT License. You can review, modify, or contribute via our GitHub repository.

### Does it have a battery?
No. ZeroKeyUSB is powered through USB-C and has no internal battery, meaning there’s nothing to charge or replace.

### Can I use it on multiple devices?
Yes. Since ZeroKeyUSB acts like a standard HID input device, it can be used seamlessly across operating systems and devices without any configuration.

### How durable is the device?
ZeroKeyUSB is designed to be water-, dust-, and tamper-resistant. With no moving parts or battery, it's engineered to last a lifetime.

### Can I store the same credentials on two devices?
Yes—and it’s even recommended. Carry a unit on your keychain while keeping a backup securely stored at home. This way, if you lose one, you won’t lose access to your credentials. Data can be cloned securely using the provided offline backup tool.

---

## Contributing

We welcome contributions to enhance ZeroKeyUSB! Since the firmware and design files are fully open source, feel free to review, modify, and submit pull requests. For suggestions, bug reports, or further improvements, please open an issue in this repository.

---

## License

ZeroKeyUSB is released under the [MIT License](LICENSE). See the LICENSE file for additional details.
