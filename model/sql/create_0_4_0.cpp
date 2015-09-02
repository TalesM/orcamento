//OrcaMento. A small program to manage finances.
//Copyright (C) 2015  talesm <tales.miranda88@gmail.com>
//
//This program is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.
//
//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with this program.  If not, see <http://www.gnu.org/licenses/>.
#include "create_0_4_0.h"

namespace v0_4_0{
    
const char *createScript = R"sql(
PRAGMA foreign_keys = ON;

DROP VIEW IF EXISTS "execution";

DROP TABLE IF EXISTS "meta";
DROP TABLE IF EXISTS "wallet";
DROP TABLE IF EXISTS "budget";
DROP TABLE IF EXISTS "category";
DROP TABLE IF EXISTS "estimate";
DROP TABLE IF EXISTS "execution";
DROP TABLE IF EXISTS "movement";

DROP TRIGGER IF EXISTS "wallet_insert";
DROP TRIGGER IF EXISTS "wallet_update";
DROP TRIGGER IF EXISTS "wallet_delete";
DROP TRIGGER IF EXISTS "budget_insert";
DROP TRIGGER IF EXISTS "budget_update";
DROP TRIGGER IF EXISTS "budget_delete";
DROP TRIGGER IF EXISTS "estimate_insert";
DROP TRIGGER IF EXISTS "estimate_update";
DROP TRIGGER IF EXISTS "estimate_delete";
DROP TRIGGER IF EXISTS "execution_insert";
DROP TRIGGER IF EXISTS "execution_update";
DROP TRIGGER IF EXISTS "execution_delete";
DROP TRIGGER IF EXISTS "movement_insert";
DROP TRIGGER IF EXISTS "movement_update";
DROP TRIGGER IF EXISTS "movement_delete";

CREATE TABLE "wallet" (
	"wallet_id"		INTEGER PRIMARY KEY,
	"name"			VARCHAR UNIQUE NOT NULL,
	"obs"			TEXT
);
INSERT INTO `wallet` (wallet_id,name,obs) VALUES (1,'Pocket','adfdsf'),
 (2,'Bank',NULL);
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

CREATE TABLE "meta" (
    "key"           VARCHAR PRIMARY KEY,
    "value"         TEXT
);
INSERT INTO `meta` (key,value) VALUES ('format-name','orcamento'),
 ('format-version','0.4.0');
CREATE TABLE "estimate" (
	"estimate_id"	INTEGER PRIMARY KEY,
	"budget_id"		INTEGER NOT NULL REFERENCES budget(budget_id),
	"category_id"	INTEGER NOT NULL REFERENCES category(category_id),
	"name"			VARCHAR,
	"amount"		INTEGER NOT NULL CHECK (typeof(amount) = 'integer'),
	"due"			TEXT NOT NULL DEFAULT(strftime('%d', 'now') || ' days'), --Must be a date offset MM UNIT, to be applied on bugdet.start.
	"obs"			TEXT,

	CONSTRAINT "u_name_per_budget" UNIQUE ("budget_id", "name")
);

CREATE TABLE "category" (
	"category_id"	INTEGER PRIMARY KEY,
	"name"			VARCHAR UNIQUE NOT NULL,
	"obs"			TEXT
);
INSERT INTO `category` (category_id,name,obs) VALUES (1,'Income',NULL),
 (2,'Habitation',NULL),
 (3,'Transport',NULL),
 (4,'Food',NULL),
 (5,'Personal Care',NULL),
 (6,'Entertainment',NULL),
 (7,'Comestimates',NULL),
 (8,'Economy and Investments',NULL),
 (9,'Taxes',NULL),
 (10,'Gifts',NULL),
 (11,'Extras',NULL);
CREATE TABLE "budget" (
	"budget_id"		INTEGER PRIMARY KEY,
	"name"			VARCHAR UNIQUE,
	"start"			DATE NOT NULL, --Must be a date YYYY-MM-DD.
	"duration"		TEXT NOT NULL, --Must be a date offset MM UNIT.
	"executing"		INTEGER NOT NULL DEFAULT 0
);

CREATE VIEW "execution" AS 
SELECT movement_id AS "execution_id", "estimate_id", "description", "date", "obs",
	(CASE WHEN credit_wallet_id IS NULL THEN -"amount" ELSE "amount" END) AS "amount",
	IFNULL(credit_wallet_id, debit_wallet_id) AS "wallet_id"
FROM movement
WHERE debit_wallet_id IS NULL OR credit_wallet_id IS NULL;

CREATE TRIGGER "update_insert" INSTEAD OF UPDATE ON "execution" FOR EACH ROW
BEGIN
	INSERT OR REPLACE INTO movement("movement_id", "estimate_id", "description", "amount", "date", "obs", "debit_wallet_id", "credit_wallet_id") 
	VALUES (
		NEW."execution_id", NEW."estimate_id", NEW."description", ABS(NEW."amount"), NEW."date", NEW."obs", 
		(CASE WHEN NEW."amount" < 0 THEN NEW."wallet_id" ELSE NULL END),
		(CASE WHEN NEW."amount" < 0 THEN NULL ELSE NEW."wallet_id" END)
	);
END;
CREATE TRIGGER "movement_insert" AFTER INSERT ON "movement" FOR EACH ROW
BEGIN
    SELECT CASE WHEN NOT executing THEN RAISE(FAIL, 'Budget not executing') END
        FROM "estimate"
            JOIN "budget" USING("budget_id")
        WHERE estimate_id = NEW.estimate_id AND "category_id" NOT NULL;
END;
CREATE TRIGGER "execution_insert" INSTEAD OF INSERT ON "execution" FOR EACH ROW
BEGIN
	INSERT INTO movement("movement_id", "estimate_id", "description", "amount", "date", "obs", "debit_wallet_id", "credit_wallet_id") 
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
CREATE TRIGGER "budget_update" AFTER UPDATE OF "executing" ON "budget" FOR EACH ROW
BEGIN
    SELECT CASE WHEN OLD.executing = 1 AND NEW.executing = 0 THEN RAISE(FAIL, 'Can not deactivate') END;
    SELECT CASE WHEN prev.executing = 0 AND NEW.executing = 1 THEN RAISE(FAIL, 'Can not execute before previous') END
        FROM "budget" prev
        WHERE "budget_id" = NEW.budget_id-1;
END;
CREATE TRIGGER "budget_insert" AFTER INSERT ON "budget" FOR EACH ROW
BEGIN
    SELECT CASE WHEN executing = 0 AND NEW.executing = 1 THEN RAISE(FAIL, 'Can not execute before previous') END
        FROM "budget"
        WHERE "budget_id" = NEW.budget_id-1;
END;

)sql";
}