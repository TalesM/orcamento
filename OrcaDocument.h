#ifndef _ORCADOCUMENT_H
#define _ORCADOCUMENT_H

#include <string>
#include <memory>
#include <SQLiteCpp/Database.h>
#include <SQLiteCpp/Transaction.h>
#include "OrcaAction.h"
#include "OrcaView.h"

/** @brief A document
 */
class OrcaDocument
{
public:
    /** \brief
     *
     * \param path the destiny.
     * \param erase if true, it creates a new file.
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

    template<typename Action, typename ...ARGS>
    auto exec(ARGS ...args)
    {
        static_assert(std::is_base_of<OrcaAction, Action>::value, "You must give class derived from action as base class.");
        std::unique_ptr<OrcaAction> action = std::make_unique<Action>(args...);
        action->doAction(_model);
        return _model.getLastInsertRowid();
        // TODO (Tales#1#): Push
    }

    template<typename ...ARGS>
    void look(OrcaView<ARGS...> &view, typename OrcaView<ARGS...>::HANDLER handler)
    {
        view.look(_model, handler);
    }
//private:
    SQLite::Database _model;
};

#endif // _ORCADOCUMENT_H
