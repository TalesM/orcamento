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
#include "create_0_2_0.h"

namespace v0_2_0{
    
const char *createScript = R"sql(
PRAGMA foreign_keys = ON;

DROP TABLE IF EXISTS "meta";
DROP TABLE IF EXISTS "wallet";
DROP TABLE IF EXISTS "budget";
DROP TABLE IF EXISTS "estimate";
DROP TABLE IF EXISTS "execution";
DROP TABLE IF EXISTS "category";

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

CREATE TABLE "meta" (
    "key"           VARCHAR PRIMARY KEY,
    "value"         TEXT
);
CREATE TABLE "wallet" (
	"wallet_id"		INTEGER PRIMARY KEY,
	"name"			VARCHAR UNIQUE NOT NULL,
	"obs"			TEXT
);
CREATE TABLE "budget" (
	"budget_id"		INTEGER PRIMARY KEY,
	"name"			VARCHAR UNIQUE,
	"start"			DATE NOT NULL, --Must be a date YYYY-MM-DD.
	"duration"		TEXT NOT NULL, --Must be a date offset MM UNIT.
	"executing"		INTEGER NOT NULL DEFAULT 0
);
CREATE TABLE "category" (
	"category_id"	INTEGER PRIMARY KEY,
	"name"			VARCHAR UNIQUE NOT NULL,
	"obs"			TEXT
);
CREATE TABLE "estimate" (
	"estimate_id"	INTEGER PRIMARY KEY,
	"budget_id"		INTEGER NOT NULL REFERENCES budget(budget_id),
	"category_id"	INTEGER NOT NULL REFERENCES category(category_id),
	"name"			VARCHAR,
	"amount"		INTEGER NOT NULL CHECK (typeof(amount) = 'integer'),
	"due"			TEXT, --Must be a date offset MM UNIT, to be applied on bugdet.start.
	"obs"			TEXT,

	CONSTRAINT "u_name_per_budget" UNIQUE ("budget_id", "name")
);
CREATE TABLE "execution" (
	"execution_id"	INTEGER PRIMARY KEY,
	"estimate_id"	INTEGER NOT NULL REFERENCES estimate(estimate_id),
	"wallet_id"		INTEGER NOT NULL REFERENCES wallet(wallet_id),
	"description"   VARCHAR,
	"amount"		INTEGER NOT NULL CHECK (typeof(amount) = 'integer'),
	"date"			TEXT NOT NULL DEFAULT CURRENT_DATE, --Must be a date YYYY-MM-DD.
	"obs"			TEXT
);

--Budget triggers
CREATE TRIGGER "budget_insert" AFTER INSERT ON "budget" FOR EACH ROW
BEGIN
    SELECT CASE WHEN executing = 0 AND NEW.executing = 1 THEN RAISE(FAIL, 'Can not execute before previous') END
        FROM "budget"
        WHERE "budget_id" = NEW.budget_id-1;
END;
CREATE TRIGGER "budget_update" AFTER UPDATE OF "executing" ON "budget" FOR EACH ROW
BEGIN
    SELECT CASE WHEN OLD.executing = 1 AND NEW.executing = 0 THEN RAISE(FAIL, 'Can not deactivate') END;
    SELECT CASE WHEN prev.executing = 0 AND NEW.executing = 1 THEN RAISE(FAIL, 'Can not execute before previous') END
        FROM "budget" prev
        WHERE "budget_id" = NEW.budget_id-1;
END;

--Exectuion Triggers
CREATE TRIGGER "execution_insert" AFTER INSERT ON "execution" FOR EACH ROW
BEGIN
    SELECT CASE WHEN NOT executing THEN RAISE(FAIL, 'Budget not executing') END
        FROM "estimate"
            JOIN "budget" USING("budget_id")
        WHERE estimate_id = NEW.estimate_id AND "category_id" NOT NULL;
END;

INSERT INTO "meta"("key", "value")
VALUES
    ('format-name', 'orcamento'),
    ('format-version', '0.2.0');

INSERT INTO "category"(name)
VALUES
    ('Income'),
    ('Habitation'),
    ('Transport'),
    ('Food'),
    ('Personal Care'),
    ('Entertainment'),
    ('Comestimates'),
    ('Economy and Investments'),
    ('Taxes'),
    ('Gifts'),
    ('Extras');

INSERT INTO "wallet"(name)
VALUES
    ('Pocket'),
    ('Bank');
)sql";
}