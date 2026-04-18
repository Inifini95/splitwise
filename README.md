# Splitwise Backend System (C++)

## 📌 Overview

This project is a **low-level design (LLD) implementation of a Splitwise-like expense sharing system** built in modern C++.
It focuses on **clean architecture, extensibility, and memory-safe design**, while supporting multiple expense splitting strategies.

The system currently runs as a **CLI-based backend simulation**, with plans to extend into a **REST API service**.

---

## 🚀 Features

* Add users to the system
* Record expenses with different split strategies:

  * Equal Split
  * Percentage Split
* Track balances between users
* Prevent deletion of users with pending balances
* Automatic rounding handling for financial accuracy
* Extensible design to support new split types

---

## 🧠 Design Highlights

### 1. Strategy Pattern for Split Logic

Each split type is implemented as a separate strategy:

```cpp
class splitLogicService {
public:
    virtual vector<pair<string,double>> split(...) = 0;
};
```

Concrete implementations:

* `equalSplitLogicService`
* `percentSplitLogicService`

👉 This allows adding new split types without modifying existing logic.

---

### 2. Input Abstraction

Instead of passing multiple parameters, a clean input hierarchy is used:

```cpp
class splitInput { ... };

class equalSplitInput : public splitInput { ... };
class percentageSplitInput : public splitInput { ... };
```

👉 Each strategy consumes only relevant data.

---

### 3. Separation of Concerns

| Layer               | Responsibility                         |
| ------------------- | -------------------------------------- |
| `splitwiseService`  | Core business logic & state management |
| `splitLogicService` | Split computation                      |
| `splitInput`        | Input modeling                         |
| `user`              | Entity                                 |

👉 Computation and state mutation are decoupled.

---

### 4. Efficient Balance Tracking

* Uses a **matrix-based ledger system**
* Maintains **net balances directly**
* Avoids recomputation

---

### 5. Memory Management (Modern C++)

* Uses `std::unique_ptr` for ownership
* No manual `new/delete`
* Automatic cleanup via RAII

```cpp
vector<unique_ptr<user>> userList;
```

---

## 🧪 Sample Flow

```cpp
splitwiseService sw;

sw.addUser("A");
sw.addUser("B");

equalSplitLogicService equalSplit;
equalSplitInput eqi;
eqi.participants = {"A","B"};

sw.addPayment(100, "A", &equalSplit, &eqi);

sw.displayBalance();
```

### Output

```
B owes 50 to A
```

---

## ⚙️ Current Limitations

* No input validation (e.g., percentage sum = 100)
* Unsafe `static_cast` usage (can be improved with validation or `dynamic_cast`)
* Fixed-size matrix (not dynamically scalable)
* No persistence (in-memory only)
* No concurrency handling
* No API layer (planned)

---

## 🛠️ Future Improvements

* [ ] Add validation layer
* [ ] Replace unsafe casts with safer alternatives
* [ ] Dynamic resizing of balance matrix
* [ ] REST API layer (planned using Drogon)
* [ ] Database integration
* [ ] Transaction history tracking
* [ ] Debt simplification algorithm (minimize transactions)

---

## 🌐 Upcoming: REST API Layer

Next step is to expose the system via REST APIs:

* `POST /users`
* `POST /expenses`
* `GET /balances`

This will convert the project into a **full backend service**.

---

## 💡 Key Learnings

* Designing extensible systems using **Strategy Pattern**
* Managing ownership using **RAII and smart pointers**
* Handling financial precision (rounding issues)
* Structuring backend systems for scalability
* Separation of logic and state

---

## 🧑‍💻 Author Notes

This project evolved iteratively from a basic implementation to a **clean, extensible architecture**, focusing on:

* correctness first
* then design
* then safety

---

## 📎 Status

✅ Core system complete
🚧 API layer in progress

---
