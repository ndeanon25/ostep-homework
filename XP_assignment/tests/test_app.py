import pytest
from app import create_app, db
from models import Task


@pytest.fixture
def client():
    app = create_app()
    app.config.update({
        'TESTING': True,
        'SQLALCHEMY_DATABASE_URI':'sqlite:///:memory:'
    })

    with app.test_client() as client:
        with app.app_context():
            db.create_all()
        yield client

def test_create_task(client):
    response = client.post('/tasks',json={'title': 'test task'})
    assert response.status_code == 200
    assert b'test task' in response.data
    assert Task.query.count() == 1

def test_delete_task(client):
    client.post('/tasks',json={'title': 'Task to be deleted'})
    response = client.delete('/tasks/1')
    assert response.status_code == 204
    assert Task.query.count() == 0

def test_mark_task_complete(client):
    client.post('/tasks',json={'title': 'Task to be completed'})
    response = client.patch('/tasks/1',json={'completed': True})
    assert response.status_code == 200
    assert b'"completed":true' in response.data
    assert Task.query.get(1).completed == True

def test_edit_task(client):
    client.post('/tasks',json={'title': 'Task to be edited'})
    response = client.patch('/tasks/1',json={'title': 'Edited task'})
    assert response.status_code == 200
    assert b'"title":"Edited task"' in response.data
    assert Task.query.get(1).title == 'Edited task'