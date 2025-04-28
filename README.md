# 🚗 Parking Management System

This **Parking Management System** is a **C++ application** designed to manage the parking of **cars, bikes, and trucks**.  
It provides functionalities for **parking, removing, displaying, and searching vehicles**, while also showing **available parking slots** for each vehicle type.  
The system ensures efficiency by utilizing **AVL trees**, **hash maps**, and **linked lists** for quick and reliable vehicle management.

---

## ✨ Key Features

### 🚘 Car Parking Management:
- Park/remove cars by **plate number**.
- Display **parked cars** and **available slots**.
- **Search** for a car by plate number.

### 🏍️ Bike Parking Management:
- Park/remove bikes by **plate number**.
- Display **parked bikes** and **available slots**.
- **Search** for a bike by plate number.

### 🚚 Truck Parking Management:
- Park/remove trucks by **slot ID**.
- Display **parked trucks** and **available slots**.
- **Search** for a truck by plate number.

### 📋 All Vehicles Management:
- View a **list of all parked vehicles** (cars, bikes, trucks).

---

## 🛠️ Data Structures Used
- **AVL Tree** ➔ manages bike parking (efficient search, insertion, deletion).
- **Hash Map** ➔ handles truck parking (fast plate number lookup).
- **Linked List** ➔ manages car parking (easy additions and removals).

---

## 📈 System Flow
The user interacts through a **menu-driven interface**, selecting the vehicle type and the desired action (e.g., **park, remove, search**).  
Input validations ensure correctness (e.g., **valid plate numbers**).

---
