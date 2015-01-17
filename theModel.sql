PRAGMA foreign_keys = ON;

DROP TABLE IF EXISTS "meta";
DROP TABLE IF EXISTS "wallet";
DROP TABLE IF EXISTS "budget";
DROP TABLE IF EXISTS "promise";
DROP TABLE IF EXISTS "execution";
DROP TABLE IF EXISTS "category";

DROP TRIGGER IF EXISTS "budget_insert";
DROP TRIGGER IF EXISTS "budget_update";
DROP TRIGGER IF EXISTS "budget_delete";
DROP TRIGGER IF EXISTS "promise_insert";
DROP TRIGGER IF EXISTS "promise_update";
DROP TRIGGER IF EXISTS "promise_delete";

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
	"name"			VARCHAR UNIQUE NOT NULL,
	"obs"			TEXT
);
CREATE TABLE "promise" (
	"promise_id"	INTEGER PRIMARY KEY,
	"budget_id"		INTEGER NOT NULL REFERENCES budget(budget_id),
	"category_id"	INTEGER REFERENCES category(category_id),
	"name"			VARCHAR NOT NULL,
	"amount"		INTEGER NOT NULL CHECK (typeof(amount) = 'integer'),
	"due"			TEXT, --Must be a date offset MM UNIT, to be applied on bugdet.start.
	"obs"			TEXT
);
CREATE TABLE "execution" (
	"execution_id"	INTEGER PRIMARY KEY,
	"promise_id"	INTEGER NOT NULL REFERENCES promise(promise_id),
	"wallet_id"		INTEGER NOT NULL REFERENCES wallet(wallet_id),
	"description"   VARCHAR,
	"amount"		INTEGER NOT NULL CHECK (typeof(amount) = 'integer'),
	"date"			TEXT NOT NULL DEFAULT CURRENT_DATE, --Must be a date YYYY-MM-DD.
	"obs"			TEXT
);

--Budget triggers
CREATE TRIGGER "budget_insert" AFTER INSERT ON "budget" FOR EACH ROW
BEGIN
    INSERT INTO "promise"("budget_id", "name", "amount") VALUES (NEW.budget_id, 'Previous Balance', IFNULL((SELECT SUM("amount") FROM "promise" WHERE "budget_id"=(NEW.budget_id-1)), 0) );
END;

--Promise Triggers
CREATE TRIGGER "promise_insert" AFTER INSERT ON "promise" FOR EACH ROW
BEGIN
    UPDATE "promise" SET "amount" = ("amount" + NEW."amount")
        WHERE "budget_id" = (NEW."budget_id" + 1) AND "category_id" IS NULL;
END;
CREATE TRIGGER "promise_update" AFTER UPDATE OF "amount" ON "promise" FOR EACH ROW
BEGIN
    UPDATE "promise" SET "amount" = ("amount" + NEW."amount" - OLD."amount")
        WHERE "budget_id" = (NEW."budget_id" + 1) AND "category_id" IS NULL;
END;
CREATE TRIGGER "promise_delete" AFTER DELETE ON "promise" FOR EACH ROW
BEGIN
    UPDATE "promise" SET "amount" = ("amount" - OLD."amount")
        WHERE "budget_id" = (OLD."budget_id" + 1) AND "category_id" IS NULL;
END;

INSERT INTO "category"(name)
VALUES
    ('Income'),
    ('Habitation'),
    ('Transport'),
    ('Food'),
    ('Personal Care'),
    ('Entertainment'),
    ('Compromises'),
    ('Economy and Investments'),
    ('Taxes'),
    ('Gifts'),
    ('Extras')
