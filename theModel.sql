CREATE TABLE "wallet" (
	"wallet_id"		INTEGER PRIMARY KEY,
	"name"			TEXT,
	"obs"			TEXT
);
CREATE TABLE "promise" (
	"promise_id"	INTEGER PRIMARY KEY,
	"budget_id"		INTEGER NOT NULL,
	"name"			TEXT NOT NULL,
	"amount"		INTEGER NOT NULL,
	"due"			TEXT,
	"obs"			TEXT,
);
CREATE TABLE "execution" (
	"execution_id"	INTEGER PRIMARY KEY,
	"promise_id"	INTEGER NOT NULL,
	"wallet_id"		INTEGER NOT NULL,
	"amount"		INTEGER NOT NULL,
	"date"			TEXT NOT NULL DEFAULT 'now',
	"obs"			TEXT,
);
CREATE TABLE "category_promise" (
	"category_id"	INTEGER PRIMARY KEY,
	"promise_id"	INTEGER UNIQUE,
);
CREATE TABLE "category_budget" (
	"category_id"	INTEGER PRIMARY KEY,
	"budget_id"		INTEGER UNIQUE,
);
CREATE TABLE "category" (
	"category_id"	INTEGER PRIMARY KEY,
	"name"			TEXT NOT NULL,
	"ob"			TEXT,
);
CREATE TABLE "budget" (
	"budget_id"		INTEGER PRIMARY KEY,
	"name"			TEXT,
	"previous_id"	INTEGER,
	"start"			TEXT NOT NULL,
	"duration"		TEXT NOT NULL,
	"closed"		INTEGER,
);
