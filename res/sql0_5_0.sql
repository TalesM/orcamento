CREATE TABLE IF NOT EXISTS "meta" (
  "key"           VARCHAR PRIMARY KEY,
  "value"         TEXT
);

INSERT OR IGNORE INTO "meta" VALUES('format-name', 'orcamento'),
  ('format-version', '0.5.0');
  
CREATE TABLE IF NOT EXISTS "budget" (
  "budget_id"   INT PRIMARY KEY,
  "name"        TEXT
);