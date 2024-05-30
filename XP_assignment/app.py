from flask import Flask,request,jsonify
from flask_sqlalchemy import SQLAlchemy


db=SQLAlchemy()

class Task(db.Model):
    id = db.Column(db.Integer,primary_key=True)
    title = db.Column(db.String(80),nullable=False)
    completed = db.Column(db.Boolean,default=False)

    def create_app():
        app = Flask(__name__)
        app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///test.db'
        app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = False
        db.init_app(app)

        @app.route('/tasks',methods=['POST'])
        def add_task():
            task_data = request.get_json()
            new_task = Task(title=task_data['title'])
            db.session.add(new_task)
            db.session.commit()
            return jsonify({'title': new_task.title}), 200
        
        @app.route('/tasks',methods=['DELETE'])
        def delete_task(id):
            task = Task.query.get_or_404(id)
            db.session.delete(task)
            db.session.commit()
            return '', 204

        @app.route('/tasks',methods=['PATCH'])
        def mark_task_complete(id):
            task = Task.query.get_or_404(id)
            task.completed = True
            db.session.add(task)
            db.session.commit()
            return jsonify({'title': task.title,'completed': task.completed}), 200

        @app.route('/tasks',methods=['PUT'])
        def edit_task(id):
            task = Task.query.get_or_404(id)
            task_data = request.get_json()
            task.title = task_data['title']
            db.session.commit()
            return jsonify({'title': task.title,'completed': task.completed}), 200

    return app

