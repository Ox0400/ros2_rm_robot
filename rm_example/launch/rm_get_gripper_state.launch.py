#!/usr/bin/python3
# -*- coding: utf-8 -*-
# @Author: zhipeng
# @Date:   2024-10-30 14:36:16
# @Last Modified By:    zhipeng
# @Last Modified: 2024-11-01 18:28:28

from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():
    ld = LaunchDescription()
    info_node = Node(
        package='rm_example', #节点所在的功能包
        executable='rm_get_gripper_state', #表示要运行的可执行文件名或脚本名字.py
        parameters= [
            {'arm_dof': 7, 'arm_type':'RM_eco65'}
        ],
        arguments=['--ros-args', '--log-level', 'DEBUG'],  ## DEBUG 模式
        output='screen', #用于将话题信息打印到屏幕
    )

    ld.add_action(info_node)
    return ld
