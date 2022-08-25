/**
 * @file       hanami_sql_table.cpp
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

#include <libKitsunemimiHanamiDatabase/hanami_sql_table.h>

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
HanamiSqlTable::HanamiSqlTable(Kitsunemimi::Sakura::SqlDatabase* db)
    : SqlTable(db)
{
    DbHeaderEntry uuid;
    uuid.name = "uuid";
    uuid.maxLength = 36;
    uuid.isPrimary = true;
    m_tableHeader.push_back(uuid);

    DbHeaderEntry projectId;
    projectId.name = "project_id";
    projectId.maxLength = 128;
    m_tableHeader.push_back(projectId);

    DbHeaderEntry ownerId;
    ownerId.name = "owner_id";
    ownerId.maxLength = 128;
    m_tableHeader.push_back(ownerId);

    DbHeaderEntry visibility;
    visibility.name = "visibility";
    visibility.maxLength = 10;
    m_tableHeader.push_back(visibility);
}

/**
 * @brief destructor
 */
HanamiSqlTable::~HanamiSqlTable() {}

/**
 * @brief add a new row to the table
 *
 * @param values json-item with key-value-pairs, which should be added as new row to the table
 * @param error reference for error-output
 *
 * @return true, if successful, else false
 */
bool
HanamiSqlTable::add(Json::JsonItem &values,
                    const std::string &userUuid,
                    const std::string &projectUuid,
                    ErrorContainer &error)
{
    // generate new uuid if the is no predefined
    if(values.contains("uuid") == false)
    {
        // create uuid
        char uuid[UUID_STR_LEN];
        uuid_t binaryUuid;
        uuid_generate_random(binaryUuid);
        uuid_unparse_lower(binaryUuid, uuid);

        // fill into string, but must be reduced by 1 to remove the escate-character
        std::string uuidString = std::string(uuid, UUID_STR_LEN - 1);
        Kitsunemimi::toLowerCase(uuidString);
        values.insert("uuid", uuidString);
    }

    // add user-ids
    values.insert("owner_id", userUuid, true);
    values.insert("project_id", projectUuid, true);

    return insertToDb(values, error);
}

/**
 * @brief get specific values for the table
 *
 * @param result reference for result-output
 * @param userUuid user-uuid to filter
 * @param projectUuid project-uuid to filter
 * @param isAdmin true, if use who makes request is admin
 * @param conditions list of conditions to filter result
 * @param error reference for error-output
 * @param showHiddenValues true to also return as hidden marked values
 *
 * @return true, if successful, else false
 */
bool
HanamiSqlTable::get(Json::JsonItem &result,
                    const std::string &userUuid,
                    const std::string &projectUuid,
                    const bool isAdmin,
                    std::vector<RequestCondition> conditions,
                    ErrorContainer &error,
                    const bool showHiddenValues)
{
    if(isAdmin == false)
    {
        conditions.emplace_back("owner_id", userUuid);
        conditions.emplace_back("project_id", projectUuid);
    }

    return getFromDb(result, conditions, error, showHiddenValues);
}

/**
 * @brief update specific values for the table
 *
 * @param values key-values-pairs to update
 * @param userUuid user-uuid to filter
 * @param projectUuid project-uuid to filter
 * @param isAdmin true, if use who makes request is admin
 * @param conditions list of conditions to filter result
 * @param error reference for error-output
 *
 * @return true, if successful, else false
 */
bool
HanamiSqlTable::update(Json::JsonItem &values,
                       const std::string &userUuid,
                       const std::string &projectUuid,
                       const bool isAdmin,
                       std::vector<RequestCondition> conditions,
                       ErrorContainer &error)
{
    if(isAdmin == false)
    {
        conditions.emplace_back("owner_id", userUuid);
        conditions.emplace_back("project_id", projectUuid);
    }

    return updateInDb(conditions, values, error);
}

/**
 * @brief get all entries of the table
 *
 * @param result reference for result-output
 * @param userUuid user-uuid to filter
 * @param projectUuid project-uuid to filter
 * @param isAdmin true, if use who makes request is admin
 * @param conditions predefined list of conditions for filtering
 * @param error reference for error-output
 * @param showHiddenValues true to also return as hidden marked values
 *
 * @return true, if successful, else false
 */
bool
HanamiSqlTable::getAll(TableItem &result,
                       const std::string &userUuid,
                       const std::string &projectUuid,
                       const bool isAdmin,
                       std::vector<RequestCondition> &conditions,
                       ErrorContainer &error,
                       const bool showHiddenValues)
{
    if(isAdmin == false)
    {
        conditions.emplace_back("owner_id", userUuid);
        conditions.emplace_back("project_id", projectUuid);
    }

    return getFromDb(result, conditions, error, showHiddenValues);
}

/**
 * @brief HanamiSqlTable::del
 *
 * @param conditions list of conditions to filter result
 * @param userUuid user-uuid to filter
 * @param projectUuid project-uuid to filter
 * @param isAdmin true, if use who makes request is admin
 * @param error reference for error-output
 *
 * @return true, if successful, else false
 */
bool
HanamiSqlTable::del(std::vector<RequestCondition> conditions,
                    const std::string &userUuid,
                    const std::string &projectUuid,
                    const bool isAdmin,
                    ErrorContainer &error)
{
    if(isAdmin == false)
    {
        conditions.emplace_back("owner_id", userUuid);
        conditions.emplace_back("project_id", projectUuid);
    }

    return deleteFromDb(conditions, error);
}

} // namespace Hanami
} // namespace Kitsunemimi
