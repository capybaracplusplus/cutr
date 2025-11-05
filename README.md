# 🪓 Cutr

**Cutr** is a lightweight and blazing-fast URL shortener written in **C++20** using the **Drogon** web framework.  
It’s designed for developers who need a simple, transparent, and efficient way to shorten links — without unnecessary complexity.

---

## 🚀 Features
- 🔗 Shorten long URLs into compact hashes
- 💾 Persistent storage in **PostgreSQL**
- ⚡ Caching layer powered by **Redis**
- 🧩 REST API for easy integration
- 📊 (Planned) Click tracking and analytics

---

## 🧠 Architecture
Cutr follows a microservice-friendly architecture and uses the following stack:
- **C++20**
- **Drogon** web framework
- **PostgreSQL** for persistent data storage
- **Redis** for caching and hash de-duplication

Each shortened URL is stored in the database with a unique ID and creation timestamp. Redis caching ensures instant lookups and minimal latency.

---

## 💡 API Example

### Shorten a link
**POST** `/shorten`
```json
{
  "url": "https://example.com/some/very/long/link"
}
```

**Response**
```
{
  "short_url": "https://cutr.io/aB3xC9"
}
```
