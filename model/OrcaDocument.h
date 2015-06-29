#ifndef _ORCADOCUMENT_H
#define _ORCADOCUMENT_H

#include <string>
#include <memory>
#include <SQLiteCpp/Database.h>
#include <SQLiteCpp/Transaction.h>
#include "OrcaAction.h"
#include "OrcaView.h"

namespace fileFormat{
constexpr int MAJOR = 0, MINOR = 2, PATCH = 0, VARIANT = 0;
}

struct wrongver_error: public std::runtime_error{
    int major, minor, patch, variant;
    wrongver_error(int major, int minor, int patch, int variant = 0):
        std::runtime_error("Wrong File Format Version"),
        major(major), minor(minor), patch(patch), variant(variant)
    {}

};

/** @brief A document
 */
class OrcaDocument
{
public:
    /** @brief Constructor
     *
     * @param path the destiny.
     * @param erase if true, it creates a new file.
     *
     */
    OrcaDocument(const std::string &path, bool erase=false);
    OrcaDocument(const wxString &path, bool erase=false):
        OrcaDocument(static_cast<std::string>(path.ToUTF8()), erase) {}
    ~OrcaDocument();
    static std::unique_ptr<OrcaDocument> create(const std::string &path, const wxDateTime &start);
    static std::unique_ptr<OrcaDocument> create(const wxString &path, const wxDateTime &start)
    {
        return create(static_cast<std::string>(path.ToUTF8()), start);
    }
    static std::unique_ptr<OrcaDocument> load(const std::string &path);
    static std::unique_ptr<OrcaDocument> load(const wxString &path)
    {
        return load(static_cast<std::string>(path.ToUTF8()));
    }

    static bool canConvert(int major, int minor, int patch, int variant);
    static std::unique_ptr<OrcaDocument> convert(const wxString &path);
    static std::unique_ptr<OrcaDocument> convert(const std::string &path)
    {
        return convert(wxString::FromUTF8(path.c_str()));
    }

    /** @brief execute an action.
     *
     * @tparam Action the action type to be executed.
     * @param ...args  the arguments (delegated to the action)
     * @return the last inserted rowid. Use it wisely.
     *
     */
    template<typename Action, typename ...ARGS>
    auto exec(ARGS ...args)
    {
        transaction();
        static_assert(std::is_base_of<OrcaAction, Action>::value, "You must give class derived from action as base class.");
        std::unique_ptr<OrcaAction> action = std::make_unique<Action>(std::forward<ARGS>(args)...);
        action->doAction(_model);
        return _model.getLastInsertRowid();
        // TODO (Tales#1#): Push
    }

    /** @brief Iterate over a view giving it a look
     *
     * @param view The view to be iterated
     * @param handler a callback that will iterate the view.
     *
     */
    template<typename ...ARGS>
    void look(OrcaView<ARGS...> &view, typename OrcaView<ARGS...>::HANDLER handler)
    {
        view.look(_model, handler);
    }

    /** @brief Return whether the document has pending changes
     *
     * Pendings changes means "need to be saved"
     * @return bool
     *
     */
    bool dirt() const {
        return bool(_transaction);
    }

    /** @brief Save the document.
     *
     * Commit changes.
     *
     */
    void save();
protected:
    std::unique_ptr<SQLite::Transaction> &transaction();
private:
    SQLite::Database _model;
    std::unique_ptr<SQLite::Transaction> _transaction;
};

#endif // _ORCADOCUMENT_H
