-- 酒店入住与预订管理系统数据库表创建脚本
-- 版本: 1.0
-- 创建日期: 2026-01-13

-- 启用外键约束
PRAGMA foreign_keys = ON;

-- 1. 房型表
CREATE TABLE IF NOT EXISTS room_type (
    type_id INTEGER PRIMARY KEY AUTOINCREMENT,
    name TEXT NOT NULL,
    area REAL NOT NULL,
    bed_type TEXT NOT NULL,
    price_per_day REAL NOT NULL,
    facilities TEXT,
    total_rooms INTEGER NOT NULL,
    available_rooms INTEGER NOT NULL
);

-- 2. 房间表
CREATE TABLE IF NOT EXISTS room (
    room_id INTEGER PRIMARY KEY AUTOINCREMENT,
    room_number TEXT NOT NULL UNIQUE,
    type_id INTEGER NOT NULL,
    floor INTEGER NOT NULL,
    status TEXT NOT NULL DEFAULT '空闲', -- 状态：空闲、已预订、已入住、维修中
    FOREIGN KEY (type_id) REFERENCES room_type(type_id) ON DELETE CASCADE
);

-- 3. 客户表
CREATE TABLE IF NOT EXISTS customer (
    customer_id INTEGER PRIMARY KEY AUTOINCREMENT,
    name TEXT NOT NULL,
    id_card TEXT NOT NULL UNIQUE,
    phone TEXT NOT NULL
);

-- 4. 订单表
CREATE TABLE IF NOT EXISTS order_info (
    order_id INTEGER PRIMARY KEY AUTOINCREMENT,
    customer_id INTEGER NOT NULL,
    room_id INTEGER NOT NULL,
    check_in_date DATE NOT NULL,
    check_out_date DATE NOT NULL,
    actual_check_out_date DATE,
    status TEXT NOT NULL DEFAULT '已预订', -- 状态：已预订、已入住、已结算、已取消
    total_amount REAL,
    FOREIGN KEY (customer_id) REFERENCES customer(customer_id) ON DELETE CASCADE,
    FOREIGN KEY (room_id) REFERENCES room(room_id) ON DELETE CASCADE
);

-- 5. 结算表
CREATE TABLE IF NOT EXISTS settlement (
    settlement_id INTEGER PRIMARY KEY AUTOINCREMENT,
    order_id INTEGER NOT NULL UNIQUE,
    payment_method TEXT NOT NULL,
    payment_amount REAL NOT NULL,
    settlement_date DATETIME NOT NULL,
    notes TEXT,
    FOREIGN KEY (order_id) REFERENCES order_info(order_id) ON DELETE CASCADE
);

-- 插入测试数据
-- 房型数据
INSERT INTO room_type (name, area, bed_type, price_per_day, facilities, total_rooms, available_rooms) VALUES
('标准间', 25.0, '双床', 288.0, '空调,电视,独立卫浴,免费WiFi', 10, 10),
('大床房', 28.0, '大床', 328.0, '空调,电视,独立卫浴,免费WiFi,迷你吧', 8, 8),
('豪华套房', 45.0, '大床', 588.0, '空调,电视,独立卫浴,免费WiFi,迷你吧,沙发,办公桌', 5, 5),
('家庭房', 35.0, '双床+单人床', 428.0, '空调,电视,独立卫浴,免费WiFi,儿童玩具', 6, 6);

-- 房间数据
-- 标准间 (type_id=1)
INSERT INTO room (room_number, type_id, floor, status) VALUES
('101', 1, 1, '空闲'),
('102', 1, 1, '空闲'),
('103', 1, 1, '空闲'),
('201', 1, 2, '空闲'),
('202', 1, 2, '空闲'),
('203', 1, 2, '空闲'),
('301', 1, 3, '空闲'),
('302', 1, 3, '空闲'),
('401', 1, 4, '空闲'),
('402', 1, 4, '空闲');

-- 大床房 (type_id=2)
INSERT INTO room (room_number, type_id, floor, status) VALUES
('104', 2, 1, '空闲'),
('105', 2, 1, '空闲'),
('204', 2, 2, '空闲'),
('205', 2, 2, '空闲'),
('304', 2, 3, '空闲'),
('305', 2, 3, '空闲'),
('404', 2, 4, '空闲'),
('405', 2, 4, '空闲');

-- 豪华套房 (type_id=3)
INSERT INTO room (room_number, type_id, floor, status) VALUES
('501', 3, 5, '空闲'),
('502', 3, 5, '空闲'),
('601', 3, 6, '空闲'),
('602', 3, 6, '空闲'),
('701', 3, 7, '空闲');

-- 家庭房 (type_id=4)
INSERT INTO room (room_number, type_id, floor, status) VALUES
('106', 4, 1, '空闲'),
('206', 4, 2, '空闲'),
('306', 4, 3, '空闲'),
('406', 4, 4, '空闲'),
('506', 4, 5, '空闲'),
('606', 4, 6, '空闲');
