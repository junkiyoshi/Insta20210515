#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(0);
	ofSetLineWidth(2);
	ofEnableDepthTest();

	this->line.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->face.clear();
	this->line.clear();

	auto log = 13;

	for (int k = 0; k < 2; k++) {

		auto noise_seed = glm::vec3(ofRandom(1000), ofRandom(1000), ofRandom(1000));
		auto base_noise_seed = glm::vec3(ofRandom(1000), ofRandom(1000), ofRandom(1000));
		auto base_radius_seed = ofRandom(1000);

		for (int deg = 0; deg < 360; deg += 45) {

			for (int i = 0; i <= log; i++) {

				int face_index = this->face.getNumVertices();
				int line_index = this->line.getNumVertices();

				auto base_radius = ofMap(ofNoise(base_radius_seed, (ofGetFrameNum() + i) * 0.01), 0, 1, 50, 450);
				auto len = ofMap(base_radius, 50, 450, 10, 80);

				auto rotation_x = glm::rotate(glm::mat4(), ofMap(ofNoise(noise_seed.x, (ofGetFrameNum() + i) * -0.0065), 0, 1, -PI, PI), glm::vec3(1, 0, 0));
				auto rotation_y = glm::rotate(glm::mat4(), ofMap(ofNoise(noise_seed.y, (ofGetFrameNum() + i) * -0.0065), 0, 1, -PI, PI), glm::vec3(0, 1, 0));
				auto rotation_z = glm::rotate(glm::mat4(), ofMap(ofNoise(noise_seed.z, (ofGetFrameNum() + i) * -0.0065), 0, 1, -PI, PI), glm::vec3(0, 0, 1));

				auto base_rotation_x = glm::rotate(glm::mat4(), ofMap(ofNoise(base_noise_seed.x, (ofGetFrameNum() + i) * -0.0035), 0, 1, -PI, PI), glm::vec3(1, 0, 0));
				auto base_rotation_y = glm::rotate(glm::mat4(), ofMap(ofNoise(base_noise_seed.y, (ofGetFrameNum() + i) * -0.0035), 0, 1, -PI, PI), glm::vec3(0, 1, 0));
				auto base_rotation_z = glm::rotate(glm::mat4(), ofMap(ofNoise(base_noise_seed.z, (ofGetFrameNum() + i) * -0.0035), 0, 1, -PI, PI), glm::vec3(0, 0, 1));

				vector<glm::vec3> vertices;
				vertices.push_back(glm::vec3(len * -0.5, len * 0.5, len * -0.5));
				vertices.push_back(glm::vec3(len * 0.5, len * 0.5, len * -0.5));
				vertices.push_back(glm::vec3(len * 0.5, len * 0.5, len * 0.5));
				vertices.push_back(glm::vec3(len * -0.5, len * 0.5, len * 0.5));

				vertices.push_back(glm::vec3(len * -0.5, len * -0.5, len * -0.5));
				vertices.push_back(glm::vec3(len * 0.5, len * -0.5, len * -0.5));
				vertices.push_back(glm::vec3(len * 0.5, len * -0.5, len * 0.5));
				vertices.push_back(glm::vec3(len * -0.5, len * -0.5, len * 0.5));


				auto base_location = glm::vec3(base_radius * cos(deg * DEG_TO_RAD), base_radius * sin(deg * DEG_TO_RAD), 0);

				for (auto& vertex : vertices) {

					vertex = glm::vec4(base_location, 0) * base_rotation_z * base_rotation_y * base_rotation_x + glm::vec4(vertex, 0) * rotation_z * rotation_y * rotation_x;
				}

				if (i == log) {

					this->face.addVertices(vertices);
					this->line.addVertices(vertices);

					this->face.addIndex(face_index + 0); this->face.addIndex(face_index + 1); this->face.addIndex(face_index + 2);
					this->face.addIndex(face_index + 0); this->face.addIndex(face_index + 2); this->face.addIndex(face_index + 3);

					this->face.addIndex(face_index + 4); this->face.addIndex(face_index + 5); this->face.addIndex(face_index + 6);
					this->face.addIndex(face_index + 4); this->face.addIndex(face_index + 6); this->face.addIndex(face_index + 7);

					this->face.addIndex(face_index + 0); this->face.addIndex(face_index + 4); this->face.addIndex(face_index + 1);
					this->face.addIndex(face_index + 4); this->face.addIndex(face_index + 5); this->face.addIndex(face_index + 1);

					this->face.addIndex(face_index + 1); this->face.addIndex(face_index + 5); this->face.addIndex(face_index + 6);
					this->face.addIndex(face_index + 6); this->face.addIndex(face_index + 2); this->face.addIndex(face_index + 1);

					this->face.addIndex(face_index + 2); this->face.addIndex(face_index + 6); this->face.addIndex(face_index + 7);
					this->face.addIndex(face_index + 7); this->face.addIndex(face_index + 3); this->face.addIndex(face_index + 2);

					this->face.addIndex(face_index + 3); this->face.addIndex(face_index + 7); this->face.addIndex(face_index + 4);
					this->face.addIndex(face_index + 4); this->face.addIndex(face_index + 0); this->face.addIndex(face_index + 3);


					this->line.addIndex(line_index + 0); this->line.addIndex(line_index + 1);
					this->line.addIndex(line_index + 1); this->line.addIndex(line_index + 2);
					this->line.addIndex(line_index + 2); this->line.addIndex(line_index + 3);
					this->line.addIndex(line_index + 3); this->line.addIndex(line_index + 0);

					this->line.addIndex(line_index + 4); this->line.addIndex(line_index + 5);
					this->line.addIndex(line_index + 5); this->line.addIndex(line_index + 6);
					this->line.addIndex(line_index + 6); this->line.addIndex(line_index + 7);
					this->line.addIndex(line_index + 7); this->line.addIndex(line_index + 4);

					this->line.addIndex(line_index + 0); this->line.addIndex(line_index + 4);
					this->line.addIndex(line_index + 1); this->line.addIndex(line_index + 5);
					this->line.addIndex(line_index + 2); this->line.addIndex(line_index + 6);
					this->line.addIndex(line_index + 3); this->line.addIndex(line_index + 7);
				}
				else {

					this->line.addVertices(vertices);

					if (line_index > 0 && i > 0) {

						this->line.addIndex(line_index - 8); this->line.addIndex(line_index + 0);
						this->line.addIndex(line_index - 7); this->line.addIndex(line_index + 1);
						this->line.addIndex(line_index - 6); this->line.addIndex(line_index + 2);
						this->line.addIndex(line_index - 5); this->line.addIndex(line_index + 3);

						this->line.addIndex(line_index - 4); this->line.addIndex(line_index + 4);
						this->line.addIndex(line_index - 3); this->line.addIndex(line_index + 5);
						this->line.addIndex(line_index - 2); this->line.addIndex(line_index + 6);
						this->line.addIndex(line_index - 1); this->line.addIndex(line_index + 7);
					}
				}
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	//ofRotateX(ofGetFrameNum() * 0.74);
	//ofRotateY(ofGetFrameNum() * 1.2);

	ofSetColor(0);
	this->face.draw();
	
	ofSetColor(255);
	this->line.draw();

	for (auto& vertex : this->face.getVertices()) {

		ofDrawSphere(vertex, 4);
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}