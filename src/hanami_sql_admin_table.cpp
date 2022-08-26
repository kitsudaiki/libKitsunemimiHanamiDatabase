/**
 * @file       hanami_sql_admin_table.cpp
 *
 * @author     Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 * @copyright  Apache License Version 2.0
 *
 *      Copyright 2021 Tobias Anker
 *
 *      Licensed under the Apache License, Version 2.0 (the "License");
 *      you may not use this file except in compliance with the License.
 *      You may obtain a copy of the License at
 *
 *          http://www.apache.org/licenses/LICENSE-2.0
 *
 *      Unless required by applicable law or agreed to in writing, software
 *      distributed under the License is distributed on an "AS IS" BASIS,
 *      WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *      See the License for the specific language governing permissions and
 *      limitations under the License.
 */

#include <libKitsunemimiHanamiDatabase/hanami_sql_admin_table.h>

#include <libKitsunemimiSakuraDatabase/sql_database.h>

#include <libKitsunemimiCommon/methods/string_methods.h>
#include <libKitsunemimiJson/json_item.h>

#include <uuid/uuid.h>

namespace Kitsunemimi
{
namespace Hanami
{

/**
 * @brief constructor, which add basic columns to the table
 *
 * @param db pointer to database
 */
HanamiSqlAdminTable::HanamiSqlAdminTable(Kitsunemimi::Sakura::SqlDatabase* db)
    : SqlTable(db)
{
    DbHeaderEntry id;
    id.name = "id";
    id.maxLength = 36;
    id.isPrimary = true;
    m_tableHeader.push_back(id);

    DbHeaderEntry name;
    name.name = "name";
    name.maxLength = 36;
    m_tableHeader.push_back(name);

    DbHeaderEntry creatorId;
    creatorId.name = "creator_id";
    creatorId.maxLength = 128;
    m_tableHeader.push_back(creatorId);
}

/**
 * @brief destructor
 */
HanamiSqlAdminTable::~HanamiSqlAdminTable() {}

/**
 * @brief add a new row to the table
 *
 * @param values json-item with key-value-pairs, which should be added as new row to the table
 * @param error reference for error-output
 *
 * @return true, if successful, else false
 */
bool
HanamiSqlAdminTable::add(Json::JsonItem &values,
                         ErrorContainer &error)
{
    return insertToDb(values, error);
}

/**
 * @brief get specific values for the table
 *
 * @param result reference for result-output
 * @param conditions list of conditions to filter result
 * @param error reference for error-output
 * @param showHiddenValues true to also return as hidden marked values
 *
 * @return true, if successful, else false
 */
bool
HanamiSqlAdminTable::get(Json::JsonItem &result,
                         std::vector<RequestCondition> conditions,
                         ErrorContainer &error,
                         const bool showHiddenValues)
{
    return getFromDb(result, conditions, error, showHiddenValues);
}

/**
 * @brief update specific values for the table
 *
 * @param values key-values-pairs to update
 * @param conditions list of conditions to filter result
 * @param error reference for error-output
 *
 * @return true, if successful, else false
 */
bool
HanamiSqlAdminTable::update(Json::JsonItem &values,
                            std::vector<RequestCondition> conditions,
                            ErrorContainer &error)
{
    return updateInDb(conditions, values, error);
}

/**
 * @brief get all entries of the table
 *
 * @param result reference for result-output
 * @param conditions predefined list of conditions for filtering
 * @param error reference for error-output
 * @param showHiddenValues true to also return as hidden marked values
 *
 * @return true, if successful, else false
 */
bool
HanamiSqlAdminTable::getAll(TableItem &result,
                            std::vector<RequestCondition> &conditions,
                            ErrorContainer &error,
                            const bool showHiddenValues)
{
    return getFromDb(result, conditions, error, showHiddenValues);
}

/**
 * @brief HanamiSqlTable::del
 *
 * @param conditions list of conditions to filter result
 * @param error reference for error-output
 *
 * @return true, if successful, else false
 */
bool
HanamiSqlAdminTable::del(std::vector<RequestCondition> conditions,
                         ErrorContainer &error)
{
    return deleteFromDb(conditions, error);
}

} // namespace Hanami
} // namespace Kitsunemimi
