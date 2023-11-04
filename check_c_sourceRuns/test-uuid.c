#include <uuid/uuid.h>

int main(int argc, char *argv[]) {
  uuid_t uuid;

  uuid_generate(uuid);

  return 0;
}
