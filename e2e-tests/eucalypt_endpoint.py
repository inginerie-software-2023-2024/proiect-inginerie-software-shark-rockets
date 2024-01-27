import requests

class APIRequester:
    def __init__(self, base_url, headers):
        self.base_url = base_url
        self.headers = headers

    def post(self, endpoint, payload):
        url = f"{self.base_url}/{endpoint}"
        response = requests.post(url, json=payload, headers=self.headers)
        return response.json()

    def get(self, endpoint, headers=None):
        url = f"{self.base_url}/{endpoint}"
        effective_headers = self.headers if headers is None else headers
        response = requests.get(url, headers=effective_headers)
        return response.json()

BASE_URL = "http://localhost:8080"
HEADERS = {"Content-Type": "application/vnd.api+json"}
eucalypt_api = APIRequester(BASE_URL, HEADERS)

def login(email, password):
    payload = {
        "data": {
            "attributes": {
                "email": email,
                "password": password
            }
        }
    }
    return eucalypt_api.post("login", payload)

def register(name, email, password):
    payload = {
        "data": {
            "attributes": {
                "name": name,
                "email": email,
                "password": password
            }
        }
    }
    return eucalypt_api.post("register", payload)

def generate_token(id):
    return eucalypt_api.get(f"connection/generateToken/{id}")

def get_me(token):
    auth_headers = HEADERS.copy()
    auth_headers["Authorization"] = f"Bearer {token}"
    return eucalypt_api.get("me", auth_headers)

def get_id(email,password):
    jwt = login(email, password)['access_token']
    return get_me(jwt)['data']['id']

if __name__ == "__main__":
    email = "test@test.com"
    password = "testtest"
    name = "test"

    my_id = get_id(email, password)

    token_response = generate_token(my_id)['id']
    print(token_response)
