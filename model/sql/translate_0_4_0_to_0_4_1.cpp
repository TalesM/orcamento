namespace v0_4_0_1{
    
const char *translateFrom0_4_0Script = R"sql(
--Create table
CREATE TABLE "budget_wallet" (
	"budget_id" INT REFERENCES budget(budget_id),
	"wallet_id" INT REFERENCES wallet(wallet_id),
	"amount" INT NOT NULL CHECK(typeof("amount") = 'integer')
);

--New field for storing budget inital value
ALTER TABLE "budget" ADD "amount" INT DEFAULT 0 NOT NULL CHECK(typeof("amount") = 'integer');

--Adding new clauses to the budget insetion
DROP TRIGGER "budget_insert";
CREATE TRIGGER "budget_insert" AFTER INSERT ON "budget" FOR EACH ROW
BEGIN
    SELECT CASE WHEN executing = 0 AND NEW.executing = 1 THEN RAISE(FAIL, 'Can not execute before previous') END
        FROM "budget"
        WHERE "budget_id" = NEW.budget_id-1;
	UPDATE "budget" SET "amount"=(SELECT b.amount + IFNULL(SUM(e.amount), 0) 
			FROM "budget" b
			LEFT JOIN "estimate" e USING("budget_id")
			WHERE "b.budget_id" = NEW.budget_id-1
		)  WHERE budget_id = NEW.budget_id;
	INSERT INTO "budget_wallet"("budget_id", "wallet_id", "amount") SELECT NEW.budget_id, wallet_id, (CASE WHEN NEW.executing THEN
			(SELECT bw.amount + IFNULL(SUM(mc.amount),0) - IFNULL(SUM(md.amount),0)
				FROM "budget_wallet" bw 
				LEFT JOIN movement mc ON mc.budget_id = NEW.budget_id -1 AND mc.credit_wallet_id = wallet.wallet_id
				LEFT JOIN movement md ON mc.budget_id = NEW.budget_id -1 AND mc.debit_wallet_id = wallet.wallet_id
				WHERE bw.budget_id = NEW.budget_id -1 AND bw.wallet_id = wallet.wallet_id
			) ELSE 0 END
		) FROM "wallet";
END;
)sql";
}