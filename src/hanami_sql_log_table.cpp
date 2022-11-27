/**
 * @file       hanami_sql_log_table.cpp
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

#include <libKitsunemimiHanamiDatabase/hanami_sql_log_table.h>

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
HanamiSqlLogTable::HanamiSqlLogTable(Kitsunemimi::Sakura::SqlDatabase* db)
    : SqlTable(db)
{
    DbHeaderEntry id;
    id.name = "timestamp";
    id.maxLength = 128;
    m_tableHeader.push_back(id);
}

/**
 * @brief destructor
 */
HanamiSqlLogTable::~HanamiSqlLogTable() {}

} // namespace Hanami
} // namespace Kitsunemimi
