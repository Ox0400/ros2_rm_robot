# 夹爪状态
bool enable             # 夹爪使能标志，0 表示未使能，1 表示使能
bool status             # 夹爪在线状态，0 表示离线， 1表示在线
uint32 error            # 夹爪错误信息，低8位表示夹爪内部的错误信息bit5-7 保留bit4 内部通bit3 驱动器bit2 过流 bit1 过温bit0 堵转
uint32 mode             # 当前工作状态：1 夹爪张开到最大且空闲，2 夹爪闭合到最小且空闲，3 夹爪停止且空闲，4 夹爪正在闭合，5 夹爪正在张开，6 夹爪闭合过程中遇到力控停止
uint32 current_force    # 夹爪当前的压力，单位g
uint32 temperature      # 当前温度，单位℃
uint32 actpos           # 夹爪开口度
