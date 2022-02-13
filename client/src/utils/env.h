//
// Created by Jason Rowland on 2/8/22.
//

#ifndef BLOCKWORLD_ENV_H
#define BLOCKWORLD_ENV_H

#include <string>

namespace utils {

void dump_env(char **envp);
auto get_env_var(std::string const &key) -> std::string;
auto get_assets_path() -> std::string;

}  // namespace utils

#endif  // BLOCKWORLD_ENV_H
