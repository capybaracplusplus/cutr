CREATE TABLE IF NOT EXISTS links (
    short_code   TEXT PRIMARY KEY,
    original_url TEXT NOT NULL,
    hits         BIGINT DEFAULT 0,
    created_at   TIMESTAMPTZ NOT NULL DEFAULT now()
);

