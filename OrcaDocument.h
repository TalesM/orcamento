#ifndef _ORCADOCUMENT_H
#define _ORCADOCUMENT_H

#include <string>
#include <memory>
#include <SQLiteCpp/Database.h>
#include <SQLiteCpp/Transaction.h>

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
        OrcaDocument(static_cast<std::string>(path.ToUTF8()), erase){}
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
//private:
    SQLite::Database _model;
};

#endif // _ORCADOCUMENT_H
