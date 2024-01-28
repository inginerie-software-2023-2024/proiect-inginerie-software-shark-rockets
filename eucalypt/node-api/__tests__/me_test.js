import request from 'supertest';
import express from 'express';
import { getProfileRouteHandler, patchProfileRouteHandler } from '../src/services/me/index'; // Replace with the actual file path

const app = express();

// Mock the user object for testing
const mockUser = {
  id: '123',
  name: 'Test User',
  email: 'test@example.com',
  role: 'user',
  createdAt: new Date(),
  updatedAt: new Date()
};

// Mock the request object with a user property
const mockRequest = {
  user: mockUser
};

app.get('/profile', (req, res) => getProfileRouteHandler(mockRequest, res));
app.patch('/profile2', express.json(), (req, res) => patchProfileRouteHandler(req, res));

describe('getProfileRouteHandler', () => {
  it('should return user profile data', async () => {
    const response = await request(app).get('/profile');
    expect(response.status).toBe(200);
    expect(response.body.data.attributes.name).toBe(mockUser.name);
  });
});
