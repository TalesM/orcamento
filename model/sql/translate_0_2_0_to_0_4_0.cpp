namespace v0_4_0{
    
const char *translateFrom0_2_0Script = R"sql(
--Create table
--New table
CREATE TABLE movement (
	"movement_id"	INTEGER PRIMARY KEY,
	"estimate_id" 	INTEGER NOT NULL REFERENCES estimate(estimate_id),
	"debit_wallet_id"	INTEGER REFERENCES wallet(wallet_id),
	"credit_wallet_id"	INTEGER REFERENCES wallet(wallet_id),
	"description"		VARCHAR,
	"amount"			INTEGER NOT NULL CHECK (typeof(amount) = 'integer' AND amount >= 0),
	"date"				TEXT NOT NULL DEFAULT CURRENT_DATE, --Must be a date YYYY-MM-DD.
	"obs"				TEXT
);

--converting
INSERT INTO movement("movement_id", "estimate_id", "description", "amount", "date", "obs", "debit_wallet_id", "credit_wallet_id") 
SELECT "execution_id", "estimate_id", "description", ABS("amount"), "date", "obs", 
	(CASE WHEN "amount" < 0 THEN "wallet_id" ELSE NULL END),
	(CASE WHEN "amount" < 0 THEN NULL ELSE "wallet_id" END)
FROM execution;

--Removing old one

DROP TRIGGER "execution_insert";
DROP TABLE "execution";

--Triggers
CREATE TRIGGER "movement_insert" AFTER INSERT ON "movement" FOR EACH ROW
BEGIN
    SELECT CASE WHEN NOT executing THEN RAISE(FAIL, 'Budget not executing') END
        FROM "estimate"
            JOIN "budget" USING("budget_id")
        WHERE estimate_id = NEW.estimate_id AND "category_id" NOT NULL;
END;

--Compatibility View
CREATE VIEW "execution" AS 
SELECT movement_id AS "execution_id", "estimate_id", "description", "date", "obs",
	(CASE WHEN credit_wallet_id IS NULL THEN -"amount" ELSE "amount" END) AS "amount",
	IFNULL(credit_wallet_id, debit_wallet_id) AS "wallet_id"
FROM movement
WHERE debit_wallet_id IS NULL OR credit_wallet_id IS NULL
;

--Compatibility triggers
CREATE TRIGGER "execution_insert" INSTEAD OF INSERT ON "execution" FOR EACH ROW
BEGIN
	INSERT INTO movement("movement_id", "estimate_id", "description", "amount", "date", "obs", "debit_wallet_id", "credit_wallet_id") 
	VALUES (
		NEW."execution_id", NEW."estimate_id", NEW."description", ABS(NEW."amount"), NEW."date", NEW."obs", 
		(CASE WHEN NEW."amount" < 0 THEN NEW."wallet_id" ELSE NULL END),
		(CASE WHEN NEW."amount" < 0 THEN NULL ELSE NEW."wallet_id" END)
	);
END;

CREATE TRIGGER "update_insert" INSTEAD OF UPDATE ON "execution" FOR EACH ROW
BEGIN
	INSERT OR REPLACE INTO movement("movement_id", "estimate_id", "description", "amount", "date", "obs", "debit_wallet_id", "credit_wallet_id") 
	VALUES (
		NEW."execution_id", NEW."estimate_id", NEW."description", ABS(NEW."amount"), NEW."date", NEW."obs", 
		(CASE WHEN NEW."amount" < 0 THEN NEW."wallet_id" ELSE NULL END),
		(CASE WHEN NEW."amount" < 0 THEN NULL ELSE NEW."wallet_id" END)
	);
END;

CREATE TRIGGER "delete_insert" INSTEAD OF DELETE ON "execution" FOR EACH ROW
BEGIN
	DELETE FROM movement WHERE "movement_id" = NEW."execution_id";
END;

UPDATE "meta" SET "value" = '0.4.0' WHERE "key" = 'format-version';
)sql";
}