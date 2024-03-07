# Image Signal Process For HDR CMOS Image Sensor

**[EN](../readme.md) | [CH](./readme_ch.md)**

# 项目描述


**一个使用C++编写的、用于HDR相机的ISP Pipeline**

- ISP模块使用C风格编写
- 没有其他库依赖
- 可以在任意嵌入式平台上部署
- 可以自定义你的pipeline通过json配置

# 默认Pipeline

![Pipeline](pipeline.png)

# 支持的ISP模块列表

- Raw Domain
    - [x] MipiUnPack: Mipi原始数据转RAW16
    - [x] DePwl: 解压缩数据
    - [x] Dpc: 动态坏点校准（TBD）
    - [x] Lsc: 镜头阴影校准（TBD）
    - [x] Blc: 黑电平校准
    - [x] Rns: Raw域降噪
    - [x] WbGain: 白平衡增益
    - [x] Demoasic: 解马赛克
- RGB Domain
    - [x] Ltm: 局部色调映射
    - [x] RgbGamma: rgb伽马曲线
    - [x] Ccm: 色彩校准矩阵
    - [x] Rgb2Yuv: rgb域转yuv域
- YUV Domain
    - [x] YGamma: 灰度伽马曲线
    - [x] Contrast: 对比度提升
    - [x] Sharpen: 锐化边缘增强
    - [x] Cns: 颜色滤波（TBD）
    - [x] Saturation: 色度提升
    - [x] Yuv2Rgb: yuv域rgb域
 

# 如何编译与运行

## Linux系统
**开发环境:** 
```bash
#dependencies install(cmake and opencv)
sudo apt update
sudo apt install cmake
```

**编译**

```bash
git clone https://github.com/JokerEyeAdas/HDR-ISP
cd HDR-ISP/
mkdir build
cmake ..
make -j12
```
## Windows系统

**开发环境(x64):** 
- vs code
- cmake
- vs2019 c++ gen tool

![build tool](compile.png) 

**编译**

```bash
git clone https://github.com/JokerEyeAdas/HDR-ISP
code HDR-ISP
#cmake 选择 Debug or Release
#compiler 选择 xxx-amd64
#build all
```

## 运行

```bash
cd build
#cp cfgs and data
cp -r ../data/ ./
cp -r ../cfgs/ ./
#run isp
./HDR_ISP ./cfgs/isp_config_cannon.json
```
## 如何调试参数

**通过修改json配置来配置ISP模块的基本参数**

如，修改sensor基本参数：
```json
    "raw_file": "./data/connan_raw14.raw",
    "out_file_path": "./",
    "info": {
        "sensor_name": "cannon",
        "cfa": "RGGB",
        "data_type": "RAW16",
        "bpp": 16,
        "max_bit": 14,
        "width": 6080,
        "height": 4044,
        "mipi_packed": 0
    },
```

修改rgb gamma参数如下：

```json
"rgbgamma": {
        "enable": true,
        "in_bit": 10,
        "out_bit": 8,
        "gammalut_nums": 11,
        "gammalut": [
            0,
            0.3504950718773984,
            0.48243595264750255,
            0.57750428843709,
            0.6596458942714417,
            0.731034378464739,
            0.7925580792857235,
            0.8509817015104557,
            0.9029435754464383,
            0.9534255851019492,
            1.0
        ]
    }
```

# 结果

## Pipeline运行结果

|备注|图像|
|-------|-------|
|Raw|![raw](ISP/connan_raw14.png)|
|ISP Result(Ours)|![ISP](ISP/isp_result.png)|
|FastOpenISP Result|![Fast ISP](ISP/color_checker.png)|

------

## 细节对比

|ISP|图像1|图像2|备注|
|-------|-------|--------|-------|
|Ours|![Our Detail](ISP/our_detail.png)|![Our Detail](ISP/our_sharpen.png)|细节与边界明显保留|
|Fast Open Isp|![Open Isp](ISP/fast_detail.png)|![Open Isp](ISP/others_sharpen.png)|细节丢失以及Color banding|

# 后续工作

* 支持Dpc、Rns、Cns等ISP模块;
* GUI ISP调试工具编写。

# 项目支持

- 感谢您的支持，希望我的项目对您有帮助

![Appreciation Code](AppreciationCode.png)

# 参考仓库

感谢下述仓库以及仓库作者！！

|序号|仓库|开发语言|备注|
|-----|-----|-----|-----|
|0|[OpenISP](https://github.com/cruxopen/openISP)|Python|image signal process in C style|
|1|[fast-openIsp](https://github.com/QiuJueqin/fast-openISP)|Python|open isp 快速版本|
|2|[ISP Lab](https://github.com/yuqing-liu-dut/ISPLab)|C++|C++版本开源ISP|
|3|[xk-ISP](https://github.com/openasic-org/xkISP)|C++|复旦大学开源HLS ISP|


# 关注我


**知乎主页：[ADAS之眼](https://www.zhihu.com/people/fen-shi-qing-nian-29) | 个人网站：[ADAS之眼](https://jokereyeadas.github.io/) | 公众号：**

**![公众号](wechat.png)**


**ADAS之眼权利保留@2023，未经允许，禁止商业用途**

-----