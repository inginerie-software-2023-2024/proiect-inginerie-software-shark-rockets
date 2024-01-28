import requests

class APIRequester:
    def __init__(self, base_url, headers):
        self.base_url = base_url
        self.headers = headers

    def post(self, endpoint, payload,headers=None):
        url = f"{self.base_url}/{endpoint}"
        effective_headers = self.headers if headers is None else headers
        response = requests.post(url, json=payload, headers=effective_headers)
        return response.json()
    
    def patch(self, endpoint, payload,headers=None):
        url = f"{self.base_url}/{endpoint}"
        effective_headers = self.headers if headers is None else headers
        response = requests.patch(url, json=payload, headers=effective_headers)
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
    return eucalypt_api.get(f"connection/generateToken/{id}")['id']

def get_profile(id,auth_headers):
    return eucalypt_api.get(f"users/getUser/{id}",auth_headers)['data']

def update_profile(id,profile,auth_headers):
    return eucalypt_api.patch(f"users/editUser/{id}",profile,auth_headers)

QUOTA_LIMIT = 1000000
def get_me(token):
    auth_headers = HEADERS.copy()
    auth_headers["Authorization"] = f"Bearer {token}"
    me = eucalypt_api.get("me", auth_headers)
    id = me['data']['id']
    
    profile = get_profile(id,auth_headers)
    old_quota = profile['quota']
    if old_quota < QUOTA_LIMIT:
        profile['quota'] = QUOTA_LIMIT
        update_profile(id,profile,auth_headers)
        # new_profile = get_profile(id,auth_headers)
        # print(f"Adjusted quota from {old_quota} to {new_profile['quota']}")
    
    return me

def get_id(email,password):
    jwt = login(email, password)['access_token']
    return get_me(jwt)['data']['id']

if __name__ == "__main__":
    email = "test@test.com"
    password = "testtest"
    name = "test"

    my_id = get_id(email, password)

    token_response = generate_token(my_id)
    print(token_response)
