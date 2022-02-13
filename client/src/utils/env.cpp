//
// Created by Jason Rowland on 2/8/22.
//

#ifndef APP_ENV_H
#define APP_ENV_H

#include <cstdio>
#include <iostream>
#include <string>

#include "executable.h"

namespace utils {

//------------------------------------------------------------------------------
// dump_env()
//------------------------------------------------------------------------------
void dump_env(char **envp) {
  std::cout << envp << std::endl;
  if (envp == nullptr) {
    printf("WARN: envp is nullptr");
    return;
  }
  // https://stackoverflow.com/questions/2085302/printing-all-environment-variables-in-c-c
  for (char **env = envp; *env != nullptr; env++) {
    char *this_env = *env;
    printf("%s\n", this_env);
  }
}

//------------------------------------------------------------------------------
// get_env_var
//------------------------------------------------------------------------------
auto get_env_var(std::string const &key) -> std::string {
  char *val = getenv(key.c_str());
  return val == nullptr ? std::string("") : std::string(val);
}

//------------------------------------------------------------------------------
// get_assets_path
//------------------------------------------------------------------------------
auto get_assets_path() -> std::string {
  auto val = get_env_var("BLOCKWORLD_ASSETS_PATH");
  if (!val.empty()) {
    return val;
  }

#ifdef __EMSCRIPTEN__
  const std::string k_dir = "";
#else
  const std::string k_dir = get_executable_dir();
#endif
  return k_dir + "/assets";
}

}  // namespace utils

#endif  // APP_ENV_H
