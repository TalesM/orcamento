#ifndef _ORCADOCUMENT_H
#define _ORCADOCUMENT_H

#include <string>
#include <memory>
#include <vector>
#include <SQLiteCpp/Database.h>
#include <SQLiteCpp/Transaction.h>
#include "OrcaAction.h"
#include "OrcaView.h"

namespace fileFormat{
constexpr int MAJOR = 0, MINOR = 4, PATCH = 0, VARIANT = 0;
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
#ifdef ORCA_WX
    OrcaDocument(const wxString &path, bool erase=false):
        OrcaDocument(static_cast<std::string>(path.ToUTF8()), erase) {}
#endif
    ~OrcaDocument();
    static std::unique_ptr<OrcaDocument> create(const std::string &path, const std::string &start);
#ifdef ORCA_WX
    static std::unique_ptr<OrcaDocument> create(const wxString &path, const wxDateTime &start)
    {
        return create(static_cast<std::string>(path.ToUTF8()), static_cast<std::string>(start.FormatISODate().ToUTF8()));
    }
#endif
    static std::unique_ptr<OrcaDocument> load(const std::string &path);
#ifdef ORCA_WX
    static std::unique_ptr<OrcaDocument> load(const wxString &path)
    {
        return load(static_cast<std::string>(path.ToUTF8()));
    }
#endif

    static bool canConvert(int major, int minor, int patch, int variant);
    static std::unique_ptr<OrcaDocument> convertFrom0_1_0(const std::string &oldPath, const std::string &newPath);
#ifdef ORCA_WX
    static std::unique_ptr<OrcaDocument> convertFrom0_1_0(const wxString &oldPath, const wxString &newPath){
        return convertFrom0_1_0(oldPath.ToUTF8(), newPath.ToUTF8());
    }
#endif
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
        static_assert(std::is_base_of<OrcaAction, Action>::value, "You must give class derived from action as base class.");
        std::unique_ptr<OrcaAction> action = std::make_unique<Action>(std::forward<ARGS>(args)...);
        return doAction(std::move(action));
    }
    
    int doAction(std::unique_ptr<OrcaAction> action);
    
    /**
     * @brief Undo the last action
     * @return Whether it still have actions to undo.
     */
    bool undo();
    
    /**
     * @brief Redo the last action
     * @return Whether it still have actions to redo.
     */
    bool redo();

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
    std::vector<std::unique_ptr<OrcaAction>> _doneActions, _undoneActions;
    std::unique_ptr<SQLite::Transaction> _transaction;
};

#endif // _ORCADOCUMENT_H
