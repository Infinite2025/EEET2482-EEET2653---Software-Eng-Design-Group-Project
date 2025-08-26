# Copilot Instructions for P2P EV Rental Project

## Project Context
This repository is for a C++ console-based backend project simulating a **peer-to-peer (P2P) electric motorbike rental system in Vietnam**.  
The system must follow **OOP principles** (classes, inheritance, polymorphism, encapsulation).  
No GUI — only **console I/O (cin, cout)**.  

## Roles
- **Guest**: view limited bike list (brand, model, capacity, location).  
- **Member**: register/login, register bike, search & request rentals, load CP, rate, manage profile.  
- **Admin**: view/manage all members, all bikes, transactions.  

## Rules
- CP = credit points (1 USD = 1 CP).  
- Registration fee = 20 USD → 20 CP.  
- Each member: 1 bike registered max, 1 active rental max.  
- Rental request conditions:
  - renter rating ≥ required rating of bike
  - enough CP
  - valid driving license if bike > 50cc
  - no other active rental
- Ratings: 1–5 stars + comments (bike and renter).  
- Balance CP cannot be negative.  
- No rental cancellation after acceptance.  

## Design Guidelines
- Use **class-based OOP design**:
  - `User` (base), subclasses `Guest`, `Member`, `Admin`.  
  - `Bike` class with attributes (brand, model, year, cc, licensePlate, rating, etc).  
  - `Rental` class for transactions.  
  - `CreditAccount` class for CP management.  
- Store data in memory (vectors, maps).  
- No database, no GUI, no external frameworks.  

## Coding Style
- Use **English identifiers**.  
- Keep functions small and modular.  
- Prefer `std::vector`, `std::map`, `std::string`.  
- Separate headers (`.h`) and implementation (`.cpp`).  
- Use `enum` for role types and rental statuses.  

## Output
- Always print clear text menus and confirmations in Vietnamese.  
- Example:
  - "Welcome to our motorbike rent system!"
  - "1. Log in"
  - "2. Register"
  - "3. View motorbike list (Guest)"
  - "4. Exit"
