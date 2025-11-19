# CUTR

CUTR is a URL shortening service with support for storing and caching links in PostgreSQL and Redis. The application is written in C++ using the [Drogon](https://github.com/drogonframework/drogon) framework and is fully asynchronous.


## Screenshots

**URL Input:**
<div align="center">
  <img src="pic/url_input.png" alt="Input URL" width="400">
</div>

**Shortened Link:**
<div align="center">
  <img src="pic/short_link.png" alt="Short Link" width="400">
</div>

## Features

- Create short links for long URLs
- Redirect from a short link to the original URL
- Cache links in Redis to speed up redirects
- Track link usage statistics (hit counts)
- Persistent storage using PostgreSQL

## Architecture

- **Controllers**: `LinkController` handles API endpoints for creating and redirecting links
- **Services**: `LinkService` and `RedirectService` implement business logic
- **Repositories**: interact with data through the `ILinkRepository` interface and concrete implementations for PostgreSQL and Redis
- **Caching**: Redis is used for fast lookup and redirect
- **Asynchronous**: all database and cache operations are performed in coroutines


## API Examples

Below are the primary endpoints exposed by CUTR.  
All responses are JSON.

### Create a short link

**POST** `/shorten`

#### Request body:

```json
{
  "url": "https://www.youtube.com/watch?v=dQw4w9WgXcQ"
}
```

#### Example request:
```bash
curl -X POST http://localhost:8080/shorten \
-H "Content-Type: application/json" \
-d '{"url": "https://www.youtube.com/watch?v=dQw4w9WgXcQ"}'
```

#### Example response:
```json
{
    "shortCode": "r/AbC123"
}
```

### Redirect to the original URL

**GET** `/{short-code}`

#### Example request:
```bash
curl http://localhost:8080/r/AbC123
```

#### Example response:
```
HTTP/1.1 302 Found
Location: https://www.youtube.com/watch?v=dQw4w9WgXcQ
```

If the short link does not exist:
```
HTTP/1.1 404 Not Found
Short link not found
```



## Running with Docker

CUTR provides a fully containerized setup using `docker-compose`.  
This includes the application itself, PostgreSQL, and Redis.

### 0. Clone the repository

Make sure to clone the project together with all submodules:

```bash
git clone --recurse-submodules https://github.com/capybaracplusplus/cutr.git
```
```bash
cd cutr
```

### 1. Prepare the `.env` file

Create a `.env` file in the project root:

```env
POSTGRES_USER=postgres
POSTGRES_PASSWORD=postgres
POSTGRES_DB=cutr
POSTGRES_HOST=127.0.0.1
DB_PORT=5432

REDIS_HOST=cutr-redis
REDIS_PORT=6379

LISTEN_ADDR=0.0.0.0
LISTEN_PORT=8080
```

### 2. Build the containers

Run the following command in the project directory:

```bash
docker-compose build --no-cache
```

```bash
# Start in foreground (recommended for development)
docker-compose up
```

```bash
# Start in background
docker-compose up -d
