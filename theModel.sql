PRAGMA foreign_keys = ON;

DROP TABLE IF EXISTS "meta";
DROP TABLE IF EXISTS "wallet";
DROP TABLE IF EXISTS "budget";
DROP TABLE IF EXISTS "promise";
DROP TABLE IF EXISTS "execution";
DROP TABLE IF EXISTS "category";

DROP TRIGGER IF EXISTS "budget_insert";

CREATE TABLE "meta" (
    "key"           VARCHAR PRIMARY KEY,
    "value"         TEXT
);
CREATE TABLE "wallet" (
	"wallet_id"		INTEGER PRIMARY KEY,
	"name"			VARCHAR,
	"obs"			TEXT
);
CREATE TABLE "budget" (
	"budget_id"		INTEGER PRIMARY KEY,
	"name"			VARCHAR,
	"start"			DATE NOT NULL, --Must be a date YYYY-MM-DD.
	"duration"		TEXT NOT NULL, --Must be a date offset MM UNIT.
	"executing"		INTEGER NOT NULL DEFAULT 0
);
CREATE TABLE "category" (
	"category_id"	INTEGER PRIMARY KEY,
	"name"			VARCHAR NOT NULL,
	"obs"			TEXT
);
CREATE TABLE "promise" (
	"promise_id"	INTEGER PRIMARY KEY,
	"budget_id"		INTEGER NOT NULL REFERENCES budget(budget_id),
	"category_id"	INTEGER REFERENCES category(category_id),
	"name"			VARCHAR NOT NULL,
	"amount"		INTEGER NOT NULL,
	"due"			TEXT, --Must be a date offset MM UNIT, to be applied on bugdet.start.
	"obs"			TEXT
);
CREATE TABLE "execution" (
	"execution_id"	INTEGER PRIMARY KEY,
	"promise_id"	INTEGER NOT NULL REFERENCES promise(promise_id),
	"wallet_id"		INTEGER NOT NULL REFERENCES wallet(wallet_id),
	"description"   VARCHAR,
	"amount"		INTEGER NOT NULL,
	"date"			TEXT NOT NULL DEFAULT CURRENT_DATE, --Must be a date YYYY-MM-DD.
	"obs"			TEXT
);

CREATE TRIGGER "budget_insert" AFTER INSERT ON "budget" FOR EACH ROW
BEGIN
    INSERT INTO "promise"("budget_id", "name", "amount") VALUES (NEW.budget_id, 'Previous Balance', IFNULL((SELECT SUM("amount") FROM "promise" WHERE "budget_id"=(NEW.budget_id-1)), 0) );
END;
