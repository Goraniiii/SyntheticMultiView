# SyntheticMultiView

동국대학교 개별연구 - CSC 게임엔진을 활용한 딥러닝 분석용 데이터 생성 연구

Dongguk Univ CSE Independent Capstone Design - Research on Generating Deep Learning Analysis Data Using the Game Engine

SyntheticMultiView is a **dataset generation pipeline** built with **Unreal Engine 5.5**, designed to capture photometric, multi-view images of posed 3D scenes, along with pixel-level segmentation masks.

## Overview

This project aims to generate high-quality synthetic image data for tasks such as 3D reconstruction, segmentation, and view-consistent perception. By using a rigged hand-object setup in Unreal Engine, the system captures the same scene from multiple predefined camera viewpoints, exporting both:

- RGB images (photorealistic)
- Segmentation masks (with transparent background)

Each frame is rendered with consistent lighting, camera configuration, and visual fidelity, making it suitable for multi-view learning or synthetic supervision.

## Features

- Multi-view rendering from fixed camera positions  
- Pixel-wise segmentation masks (hand/object/background separation)  
- Photometric lighting and realistic materials  
- Fully reproducible within UE5.5 using packaged blueprint setup

## Dependencies

- Unreal Engine **5.5**
- Blender **4.22** (used for asset preprocessing and rigged animations)
- RenderTarget2D and custom post-process material setup for mask generation

## Future Work(Maybe...)

- Adding joint (pose) or Landmark coordinate export  
- Occlusion-aware visibility annotation  
- Extension to topology-aware reconstruction or NeRF-compatible data
