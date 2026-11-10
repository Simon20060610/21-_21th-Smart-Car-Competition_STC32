# 第 21 届智能车竞赛 STC32 工程

基于逐飞 STC32G144K 底层库的智能车工程，包含摄像头寻线、赛道元素识别、差速与速度控制、舵机转向及打靶控制。具体参赛组别和整车硬件型号尚未在本次整理中核实。

## 工程来源

本次发布取自 `new_2026.4.15_night/new` 当前工作树，基线为交接记录中的 `238075d`，保留 camera、vision、control 和 main 的本地源码修改。历史备份、个人文档、IDE 用户状态及编译产物不在本仓库中。

## 目录

- `libraries/`：逐飞底层库、驱动和预编译链接库。
- `project/code/`：摄像头、视觉、圆环与靶环识别。
- `project/user/`：正式程序入口和中断处理。
- `project/mdk/`：Keil 工程及控制、电机、编码器、PID、舵机、打靶模块。
- `examples/main_debug_for_shoot.c`：打靶调试入口，仅作参考，未加入正式工程；不要与正式 `main.c` 同时编译。

## 硬件与编译

源码使用 MT9V03X 摄像头接口、IMU660RA、正交编码器、电机 PWM、舵机和打靶执行机构。具体电机、舵机及开发板型号请按实车确认；引脚以各模块源码为准。

1. 在 Windows 上安装 Keil uVision 和 **MCS-251 / C251** 工具链及相应芯片支持。原工程未记录精确编译器版本。
2. 打开 `project/mdk/seekfree.uvproj`。目标名为 `stc32g144k246`，工程设备字段为 `AI8052U-32Bit Series`，请按实际芯片和设备包核对；本次整理保持原配置。
3. 保留 `libraries/zf_device/zf_device_config.LIB` 和 `libraries/zf_device/zf_device_mt9v03x_dma.LIB`，它们是工程链接依赖。
4. Build/Rebuild 后从 `project/mdk/out_file/` 获取生成的 HEX，通过与实际 STC 芯片匹配的 STC-ISP 工具及板卡下载接口烧录；端口、下载参数和供电操作以实车硬件说明为准。

本次发布已静态检查工程文件引用完整性，未执行 Keil 编译或实车验证，不附带预编译固件。首次运行前应核对电机方向、编码器方向、舵机中位和控制参数。

## 第三方版权

`libraries/` 包含 SEEKFREE（逐飞科技）的 STC32G144K 开源库及预编译库，原文件中的版权和许可声明予以保留。源码头部声明 GPL-3.0-or-later；具体文件以各自声明为准。逐飞来源入口：<https://seekfree.taobao.com/>。GPL 正文：<https://www.gnu.org/licenses/gpl-3.0.html>。

原始目录未附带头部提及的 `LICENSE` 和 `GPL3_permission_statement.txt`。本仓库未为整份工程另行指定统一许可证；项目应用代码和第三方库的权利归属应分别核实。
