# 酒店入住与预订管理系统

## 项目概述

本项目是一个基于Qt Creator和SQLite开发的酒店入住与预订管理系统，采用Model/View架构设计，实现了酒店房型管理、客户入住登记、退房结算、订单管理及房间状态实时更新等核心功能。

## 技术栈

- **开发框架**: Qt Creator (C++/Qt Widgets)
- **数据库**: SQLite
- **架构模式**: Model/View架构
- **UI设计**: Qt Designer

## 核心功能

### 1. 酒店房型管理与展示
- 支持房型增、删、改、查操作
- 核心字段：房型ID、名称、面积、床型、单日定价、配套设施、房间总数、剩余可订数
- 采用QTableView + QSqlTableModel展示房型列表
- 支持按定价排序、双击查看详情

### 2. 客户入住登记
- 可视化表单录入客户信息
- 身份证号格式校验
- 自动计算预计金额
- 仅允许选择空闲状态房间
- 支持事务处理，确保数据一致性

### 3. 客户退房结算
- 支持通过订单号、客户姓名查询待结算订单
- 自动计算实际消费金额
- 支持多种支付方式
- 生成结算凭证
- 自动更新订单状态和房间状态

### 4. 订单信息管理与多条件筛选
- 支持按入住时间范围、房型、订单状态筛选
- 采用QSqlQueryModel实现自定义查询
- 支持排序和分页
- 双击查看订单详情

### 5. 房间占用状态实时更新与展示
- 房间状态：空闲、已预订、已入住、维修中
- 实时更新房间状态（每30秒自动刷新）
- 可视化状态展示（不同颜色区分不同状态）
- 支持按状态、楼层、房型筛选

## 项目结构

```
hotelmanager/
├── dbhelper.h              # 数据库帮助类头文件
├── dbhelper.cpp            # 数据库帮助类实现
├── main.cpp                # 主函数入口
├── mainwindow.h            # 主窗口类头文件
├── mainwindow.cpp          # 主窗口类实现
├── mainwindow.ui           # 主窗口UI文件
├── roomtypemanager.h       # 房型管理类头文件
├── roomtypemanager.cpp     # 房型管理类实现
├── roomtypemanager.ui      # 房型管理UI文件
├── checkinmanager.h        # 入住管理类头文件
├── checkinmanager.cpp      # 入住管理类实现
├── checkinmanager.ui       # 入住管理UI文件
├── checkoutmanager.h       # 退房管理类头文件
├── checkoutmanager.cpp     # 退房管理类实现
├── checkoutmanager.ui      # 退房管理UI文件
├── ordermanager.h          # 订单管理类头文件
├── ordermanager.cpp        # 订单管理类实现
├── ordermanager.ui         # 订单管理UI文件
├── roomstatusmanager.h     # 房间状态管理类头文件
├── roomstatusmanager.cpp   # 房间状态管理类实现
├── roomstatusmanager.ui    # 房间状态管理UI文件
├── hotelmanager.pro        # 项目配置文件
├── hotel_db.sql            # 数据库初始化脚本
├── resources.qrc           # 资源文件
└── README.md               # 项目说明文档
```

## 数据库设计

### 表结构

1. **room_type** (房型表)
   - type_id: 房型ID (主键)
   - name: 房型名称
   - area: 面积
   - bed_type: 床型
   - price_per_day: 单日定价
   - facilities: 配套设施
   - total_rooms: 房间总数
   - available_rooms: 剩余可订数

2. **room** (房间表)
   - room_id: 房间ID (主键)
   - room_number: 房间号
   - type_id: 房型ID (外键)
   - floor: 楼层
   - status: 房间状态

3. **customer** (客户表)
   - customer_id: 客户ID (主键)
   - name: 客户姓名
   - id_card: 身份证号
   - phone: 联系方式

4. **order_info** (订单表)
   - order_id: 订单ID (主键)
   - customer_id: 客户ID (外键)
   - room_id: 房间ID (外键)
   - check_in_date: 入住日期
   - check_out_date: 退房日期
   - actual_check_out_date: 实际退房日期
   - status: 订单状态
   - total_amount: 总金额

5. **settlement** (结算表)
   - settlement_id: 结算ID (主键)
   - order_id: 订单ID (外键)
   - payment_method: 支付方式
   - payment_amount: 支付金额
   - settlement_date: 结算日期
   - notes: 备注

## 使用说明

### 环境配置

1. 安装Qt Creator 5.15或更高版本
2. 确保已安装SQLite驱动
3. 配置Qt环境变量

### 项目构建

1. 打开Qt Creator
2. 选择"打开项目"，选择hotelmanager.pro文件
3. 选择构建套件
4. 点击"构建"按钮编译项目
5. 运行项目

### 数据库初始化

首次运行时，系统会自动创建数据库文件并执行初始化脚本，创建所有表结构并插入测试数据。

## 功能模块说明

### 主窗口
- 提供功能导航菜单和工具栏
- 包含系统管理、客房管理、入住管理、退房管理、订单管理等菜单项

### 房型管理
- 点击"客房管理" → "房型管理"打开
- 支持添加、编辑、删除房型
- 支持按名称搜索

### 入住登记
- 点击"入住管理" → "入住登记"打开
- 填写客户信息、选择房型和房间、设置入住日期
- 系统自动计算预计金额

### 退房结算
- 点击"退房管理" → "退房结算"打开
- 搜索待结算订单
- 选择支付方式，完成结算

### 订单管理
- 点击"订单管理" → "订单管理"打开
- 支持多条件筛选
- 双击查看订单详情

### 房间状态
- 点击"客房管理" → "房间状态"打开
- 实时显示房间状态
- 支持按状态、楼层、房型筛选

## 项目特色

1. **采用Model/View架构**：实现数据与界面解耦，提高代码复用性和可维护性
2. **实时数据更新**：房间状态每30秒自动刷新
3. **可视化状态展示**：不同颜色区分不同房间状态
4. **事务处理**：确保数据一致性
5. **友好的用户界面**：简洁美观，操作便捷
6. **完整的异常处理**：提供用户友好的错误提示

## 注意事项

1. 请确保项目目录下存在hotel_db.sql文件
2. 首次运行时会自动创建数据库文件hotel.db
3. 数据库文件位于应用程序运行目录下
4. 建议定期备份数据库文件

## 后续优化方向

1. 增加房间预订功能
2. 实现报表统计功能
3. 支持导出订单数据
4. 增加员工管理功能
5. 实现多用户权限管理

## 联系方式

如有问题或建议，请联系项目开发团队。
