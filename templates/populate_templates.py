from jinja2 import Environment, FileSystemLoader


# Credentials setup - these are not valid defaults, they are meant to be changed
CREDENTIALS = dict([
    ['DB_LINK', "db_link"],
    ['JWT_SECRET', "token"]
])

# Compose config
COMPOSE_CONFIG = dict([
    ['CLUSTER_SUBNET', "172.7.0.0/16"],
    ['MASTER_ADDRESS', "172.7.0.10"],
    ['EUCALYPT_BACKEND_ADDRESS', "172.7.0.11"],
    ['EUCALYPT_FRONTEND_ADDRESS', "172.7.0.12"],
    ['MASTER_PORT', "50051"],
    ['WORKER_PORT', "7777"],
    ['EUCALYPT_BACKEND_PORT', "8080"],
    ['EUCALYPT_FRONTEND_PORT', "3000"],
    ['PROTO_PATH', '/app/eucalypt_service.proto'],
    ['MAP_REDUCE_IMG_TAG', "0.0.1"],
    ['EUCALYPT_BACKEND_IMG_TAG', "0.0.1"],
    ['EUCALYPT_FRONTEND_IMG_TAG', "0.0.1"],
    ['WORKER_REPLICAS', 5]
])

# Local networking
LOCAL_CONFIG = dict([
    ['MASTER_ADDRESS', "localhost"],
    ['EUCALYPT_BACKEND_ADDRESS', "localhost"],
    ['EUCALYPT_FRONTEND_ADDRESS', "localhost"],
    ['MASTER_PORT', "50051"],
    ['EUCALYPT_BACKEND_PORT', "8080"],
    ['EUCALYPT_FRONTEND_PORT', "3000"],
])


def populate_templates():
    env = Environment(
        loader = FileSystemLoader('.')
    )

    def write_render_to(path, render):
        with open(path, "w") as f:
            f.write(render)

    EUCALYPT_BACKEND_ENV_LOCAL_PATH = '../eucalypt/node-api/.env'
    EUCALYPT_BACKEND_ENV_COMPOSE_PATH = '../eucalypt/node-api/compose.env' 
    EUCALYPT_FRONTEND_ENV_LOCAL_PATH = '../eucalypt/material-react-app/.env'
    EUCALYPT_FRONTEND_ENV_COMPOSE_PATH = '../eucalypt/material-react-app/compose.env'
    DOCKER_COMPOSE_PATH = '../docker-compose.yml'

    eucalypt_backend_env_t = env.get_template('eucalypt_backend.env.jinja')
    eucalypt_backend_env_local = eucalypt_backend_env_t.render(**CREDENTIALS, **LOCAL_CONFIG)
    eucalypt_backend_env_compose = eucalypt_backend_env_t.render(**CREDENTIALS, **COMPOSE_CONFIG)
    write_render_to(EUCALYPT_BACKEND_ENV_LOCAL_PATH, eucalypt_backend_env_local)
    write_render_to(EUCALYPT_BACKEND_ENV_COMPOSE_PATH, eucalypt_backend_env_compose)

    eucalypt_frontend_env_t = env.get_template('eucalypt_frontend.env.jinja')
    eucalypt_frontend_env_local = eucalypt_frontend_env_t.render(**LOCAL_CONFIG)
    eucalypt_frontend_env_compose = eucalypt_frontend_env_t.render(**COMPOSE_CONFIG)
    write_render_to(EUCALYPT_FRONTEND_ENV_LOCAL_PATH, eucalypt_frontend_env_local)
    write_render_to(EUCALYPT_FRONTEND_ENV_COMPOSE_PATH, eucalypt_frontend_env_compose)

    docker_compose_t = env.get_template('docker-compose.yml.jinja')
    docker_compose = docker_compose_t.render(**COMPOSE_CONFIG)
    write_render_to(DOCKER_COMPOSE_PATH, docker_compose)


if __name__ == "__main__":
    if CREDENTIALS['DB_LINK'] == 'db_link':
        raise ValueError("Please populate credentials!")
    populate_templates()
