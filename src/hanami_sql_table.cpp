/**
 * @file       sql_table.cpp
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

#include <libKitsunemimiCommon/common_methods/string_methods.h>
#include <libKitsunemimiJson/json_item.h>

#include <uuid/uuid.h>

namespace Kitsunemimi
{
namespace Hanami
{

/**
 * @brief constructor
 *
 * @param db pointer to database
 */
HanamiSqlTable::HanamiSqlTable(Kitsunemimi::Sakura::SqlDatabase* db)
    : SqlTable(db)
{
    DbHeaderEntry uuid;
    uuid.name = "uuid";
    uuid.maxLength = 36;
    m_tableHeader.push_back(uuid);

    DbHeaderEntry projectUuid;
    projectUuid.name = "project_uuid";
    projectUuid.maxLength = 36;
    m_tableHeader.push_back(projectUuid);

    DbHeaderEntry owner;
    owner.name = "owner_uuid";
    owner.maxLength = 36;
    m_tableHeader.push_back(owner);

    DbHeaderEntry visibility;
    visibility.name = "visibility";
    visibility.type = INT_TYPE;
    m_tableHeader.push_back(visibility);
}

/**
 * @brief destructor
 */
HanamiSqlTable::~HanamiSqlTable() {}

/**
 * @brief HanamiSqlTable::add
 * @param values
 * @param error
 * @return
 */
bool
HanamiSqlTable::add(Json::JsonItem &values,
                    ErrorContainer &error)
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

    return insertToDb(values, error);
}

/**
 * @brief HanamiSqlTable::get
 * @param result
 * @param conditions
 * @param error
 * @return
 */
bool
HanamiSqlTable::get(Json::JsonItem &result,
                    const std::vector<RequestCondition> &conditions,
                    ErrorContainer &error,
                    const bool showHiddenValues)
{
    return getFromDb(result, conditions, error, showHiddenValues);
}

/**
 * @brief HanamiSqlTable::getAll
 * @param result
 * @param error
 * @return
 */
bool
HanamiSqlTable::getAll(TableItem &result,
                       ErrorContainer &error,
                       const bool showHiddenValues)
{
    return getAllFromDb(result, error, showHiddenValues);
}

/**
 * @brief HanamiSqlTable::del
 * @param conditions
 * @param error
 * @return
 */
bool
HanamiSqlTable::del(const std::vector<RequestCondition> &conditions,
                    ErrorContainer &error)
{
    return deleteFromDb(conditions, error);
}

} // namespace Hanami
} // namespace Kitsunemimi
